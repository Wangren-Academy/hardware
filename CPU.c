// CPU.c
#include <stdio.h>

// 执行CPUID指令
void cpuid(int code, int *a, int *b, int *c, int *d) {
    __asm__ volatile (
        "cpuid"
        : "=a"(*a), "=b"(*b), "=c"(*c), "=d"(*d)
        : "a"(code), "c"(0)
    );
}

int main() {
    int a, b, c, d;
    
    // 1. 获取CPU厂商
    cpuid(0, &a, &b, &c, &d);
    printf("CPU厂商: %.4s%.4s%.4s\n", (char*)&b, (char*)&d, (char*)&c);
    
    // 2. 获取CPU型号
    cpuid(1, &a, &b, &c, &d);
    printf("CPU型号: 家族=%d, 型号=%d, 步进=%d\n", 
           (a >> 8) & 0xF, (a >> 4) & 0xF, a & 0xF);
    
    // 3. 检查是否支持64位
    cpuid(0x80000001, &a, &b, &c, &d);
    if (d & (1 << 29)) {
        printf("支持64位: 是\n");
    }
    
    return 0;
}