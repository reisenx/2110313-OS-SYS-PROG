#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/uaccess.h>
/* Needed by all modules */
/* Needed for KERN_INFO */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KRERK PIROMSOPA, PH.D. <Krerk.P@chula.ac.th>");
MODULE_DESCRIPTION("\"cpuinfo\" Character Device");

#define DEVICENAME "cpuinfo"

static int dev_major;
static int dev_open = 0;

static char cpuinfo_buffer[256];  // buffer to store output
static char *f_ptr;

static int device_open(struct inode *inode, struct file *file)
{
    if (dev_open) return -EBUSY;
    dev_open++;

    unsigned eax, ebx, ecx, edx;

    // Vendor ID
    eax = 0;
    ecx = 0;
    native_cpuid(&eax, &ebx, &ecx, &edx);

    char vendor[13];
    ((unsigned int *)vendor)[0] = ebx;
    ((unsigned int *)vendor)[1] = edx;
    ((unsigned int *)vendor)[2] = ecx;
    vendor[12] = '\0';

    // Feature info
    eax = 1;
    native_cpuid(&eax, &ebx, &ecx, &edx);

    int stepping = eax & 0xF;
    int model = (eax >> 4) & 0xF;
    int family = (eax >> 8) & 0xF;
    int proc_type = (eax >> 12) & 0x3;
    int ext_model = (eax >> 16) & 0xF;
    int ext_family = (eax >> 20) & 0xFF;

    // Serial number
    eax = 3;
    native_cpuid(&eax, &ebx, &ecx, &edx);

    // Prepare the output
    snprintf(cpuinfo_buffer, sizeof(cpuinfo_buffer),
              "Vendor ID: %s\n"
              "Stepping: %d\n"
              "Model: %d\n"
              "Family: %d\n"
              "Processor Type: %d\n"
              "Extended Model: %d\n"
              "Extended Family: %d\n"
              "Serial Number: 0x%08x%08x\n",
              vendor, stepping, model, family, proc_type, ext_model, ext_family, edx, ecx);

    f_ptr = cpuinfo_buffer;
    try_module_get(THIS_MODULE);
    return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
    dev_open--;
    module_put(THIS_MODULE);
    return 0;
}

static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset)
{
    int bytes_read = 0;

    if (*f_ptr == 0)
        return 0;

    while (length && *f_ptr) {
        put_user(*(f_ptr++), buffer++);
        length--;
        bytes_read++;
    }

    return bytes_read;
}

static struct file_operations dev_fops = {
    .read    = device_read,
    .open    = device_open,
    .release = device_release
};

int init_module(void)
{
    printk(KERN_INFO "cpuinfo module loaded.\n");
    dev_major = register_chrdev(0, DEVICENAME, &dev_fops);

    if (dev_major < 0) {
        printk(KERN_ALERT "Registering char device failed with %d\n", dev_major);
        return dev_major;
    }

    printk(KERN_INFO "Device MajorNumber %d.\n", dev_major);
    printk(KERN_INFO "Use: mknod /dev/cpuinfo c %d 0\n", dev_major);
    return 0;
}

void cleanup_module(void)
{
    unregister_chrdev(dev_major, DEVICENAME);
    printk(KERN_INFO "cpuinfo module unloaded.\n");
}
