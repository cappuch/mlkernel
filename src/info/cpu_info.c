#include "system.h"

void get_cpu_vendor(char *vendor);
int get_cpu_cores(void);
int get_cpu_threads(void);
uint64_t get_cpu_frequency(void);
uint64_t get_ram_amount(void);

void get_cpu_vendor(char *vendor) {
    uint32_t ebx, ecx, edx;
    asm volatile("cpuid"
                 : "=b" (ebx), "=c" (ecx), "=d" (edx)
                 : "a" (0)
                 :);
    
    ((uint32_t *)vendor)[0] = ebx;
    ((uint32_t *)vendor)[1] = edx;
    ((uint32_t *)vendor)[2] = ecx;
    vendor[12] = '\0';
}

int get_cpu_cores(void) {
    uint32_t eax, ebx, ecx, edx;
    asm volatile("cpuid"
                 : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
                 : "a" (1)
                 :);
    return ((eax >> 26) & 0x3F) + 1;
}

int get_cpu_threads(void) {
    uint32_t eax, ebx, ecx, edx;
    asm volatile("cpuid"
                 : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
                 : "a" (1)
                 :);
    return ((ebx >> 16) & 0xFF);
}

void cpuid(int code, uint32_t *a, uint32_t *d) {
    asm volatile("cpuid" : "=a"(*a), "=d"(*d) : "a"(code) : "ecx", "ebx");
}