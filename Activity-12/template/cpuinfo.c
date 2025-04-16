static inline void native_cpuid(unsigned int *eax, unsigned int *ebx,
                                unsigned int *ecx, unsigned int *edx)
{
    /* ecx is often an input as well as an output. */
    asm volatile("cpuid"
                 : "=a" (*eax),
                   "=b" (*ebx),
                   "=c" (*ecx),
                   "=d" (*edx)
                 : "0" (*eax), "2" (*ecx)
                 : "memory");
}

int main(int argc, char **argv) {
    // Code snippet
    unsigned eax, ebx, ecx, edx;

    // for obtaining the features
    eax = 0; /* processor info and feature bits */
    native_cpuid(&eax, &ebx, &ecx, &edx);

    printf("Vendor ID ");
    printf("%c%c%c%c", (ebx) & 0xFF, (ebx >> 8) & 0xFF, (ebx >> 16) & 0xFF, (ebx >> 24) & 0xFF);
    printf("%c%c%c%c", (edx) & 0xFF, (edx >> 8) & 0xFF, (edx >> 16) & 0xFF, (edx >> 24) & 0xFF);
    printf("%c%c%c%c", (ecx) & 0xFF, (ecx >> 8) & 0xFF, (ecx >> 16) & 0xFF, (ecx >> 24) & 0xFF);
    printf("\n");

    // for obtaining the features
    eax = 1; /* processor info and feature bits */
    native_cpuid(&eax, &ebx, &ecx, &edx);

    printf("stepping %d\n", eax & 0xF);
    printf("model %d\n", (eax >> 4) & 0xF);
    printf("family %d\n", (eax >> 8) & 0xF);
    printf("processor type %d\n", (eax >> 12) & 0x3);
    printf("extended model %d\n", (eax >> 16) & 0xF);
    printf("extended family %d\n", (eax >> 20) & 0xFF);

    // for obtaining the serial number
    eax = 3; /* processor serial number */
    native_cpuid(&eax, &ebx, &ecx, &edx);

    printf("serial number 0x%08x%08x\n", edx, ecx);

    // For more details, see https://en.wikipedia.org/wiki/CPUID
}
