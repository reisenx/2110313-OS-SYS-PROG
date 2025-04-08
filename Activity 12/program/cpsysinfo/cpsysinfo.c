#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/sched/signal.h>  // for_each_process
#include <linux/mm.h>            // for si_meminfo
#include <linux/slab.h>          // for kzalloc

#define DEVICE_NAME "cpsysinfo"
#define CLASS_NAME "cpclass"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KRERK PIROMSOPA, PH.D. <Krerk.P@chula.ac.th>");
MODULE_DESCRIPTION("\"cpsysinfo\" Character Device");

static int majorNumber;
static struct class* cpClass = NULL;
static struct device* cpDevice0 = NULL;
static struct device* cpDevice1 = NULL;

static char *info_buffer;
static int info_size;
static int already_read = 0;

#define TO_KB(pages) ((pages) * (PAGE_SIZE / 1024))

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    int bytes_to_copy;

    if (already_read) {
        already_read = 0;
        return 0;
    }

    bytes_to_copy = min(len, (size_t)info_size);

    if (copy_to_user(buffer, info_buffer, bytes_to_copy)) {
        return -EFAULT;
    }

    already_read = 1;
    return bytes_to_copy;
}

static int dev_open(struct inode *inodep, struct file *filep) {
    int minor = MINOR(inodep->i_rdev);
    struct task_struct *task;

    if (info_buffer)
        kfree(info_buffer);

    info_buffer = kzalloc(8192, GFP_KERNEL);
    if (!info_buffer)
        return -ENOMEM;

    info_size = 0;
    already_read = 0;

    if (minor == 0) {
        // Process list
        for_each_process(task) {
            info_size += snprintf(info_buffer + info_size, 8192 - info_size,
                                  "%d,%s\n", task->pid, task->comm);
            if (info_size >= 8192 - 100)
                break;
        }
    } else if (minor == 1) {
        // Memory info
        struct sysinfo i;
        si_meminfo(&i);

        unsigned long mem_total = TO_KB(i.totalram);
        unsigned long mem_free = TO_KB(i.freeram);
        unsigned long mem_available = TO_KB(i.freeram + i.bufferram);  // simplified approximation

        info_size = snprintf(info_buffer, 8192,
                             "MemTotal: %lu kB\n"
                             "MemFree: %lu kB\n"
                             "MemAvailable: %lu kB\n",
                             mem_total, mem_free, mem_available);
    } else {
        snprintf(info_buffer, 8192, "Invalid minor number: %d\n", minor);
        info_size = strlen(info_buffer);
    }

    return 0;
}

static int dev_release(struct inode *inodep, struct file *filep) {
    return 0;
}

static struct file_operations fops = {
    .open = dev_open,
    .read = dev_read,
    .release = dev_release,
};

static int __init cpsysinfo_init(void) {
    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    if (majorNumber < 0) {
        printk(KERN_ALERT "Failed to register char device\n");
        return majorNumber;
    }

    cpClass = class_create(CLASS_NAME);  // For Linux 6.8+
    if (IS_ERR(cpClass)) {
        unregister_chrdev(majorNumber, DEVICE_NAME);
        return PTR_ERR(cpClass);
    }

    cpDevice0 = device_create(cpClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    cpDevice1 = device_create(cpClass, NULL, MKDEV(majorNumber, 1), NULL, DEVICE_NAME "1");

    if (IS_ERR(cpDevice0) || IS_ERR(cpDevice1)) {
        device_destroy(cpClass, MKDEV(majorNumber, 0));
        device_destroy(cpClass, MKDEV(majorNumber, 1));
        class_destroy(cpClass);
        unregister_chrdev(majorNumber, DEVICE_NAME);
        return -1;
    }

    printk(KERN_INFO "cpsysinfo loaded. Major number: %d\n", majorNumber);
    printk(KERN_INFO "Use:\n");
    printk(KERN_INFO "  sudo mknod /dev/cp-psinfo c %d 0\n", majorNumber);
    printk(KERN_INFO "  sudo mknod /dev/cp-meminfo c %d 1\n", majorNumber);
    return 0;
}

static void __exit cpsysinfo_exit(void) {
    if (info_buffer)
        kfree(info_buffer);
    device_destroy(cpClass, MKDEV(majorNumber, 0));
    device_destroy(cpClass, MKDEV(majorNumber, 1));
    class_unregister(cpClass);
    class_destroy(cpClass);
    unregister_chrdev(majorNumber, DEVICE_NAME);
    printk(KERN_INFO "cpsysinfo unloaded\n");
}

module_init(cpsysinfo_init);
module_exit(cpsysinfo_exit);
