// memory.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_cpuinfo() {
    FILE *f = fopen("/proc/cpuinfo", "r");
    char line[256];
    int count = 0;
    
    printf("\n=== CPU详细信息 ===\n");
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, "model name") || 
            strstr(line, "cache size") || 
            strstr(line, "cpu cores")) {
            printf("%s", line);
            count++;
        }
    }
    fclose(f);
}

void read_meminfo() {
    FILE *f = fopen("/proc/meminfo", "r");
    char line[256];
    
    printf("\n=== 内存信息 ===\n");
    for (int i = 0; i < 5; i++) {  // 只读前5行
        fgets(line, sizeof(line), f);
        printf("%s", line);
    }
    fclose(f);
}

void read_interrupts() {
    FILE *f = fopen("/proc/interrupts", "r");
    char line[256];
    
    printf("\n=== 中断统计 (前10行) ===\n");
    for (int i = 0; i < 10 && fgets(line, sizeof(line), f); i++) {
        printf("%s", line);
    }
    fclose(f);
}

int main() {
    printf("你的电脑硬件探测报告\n");
    printf("===================\n");
    
    read_cpuinfo();
    read_meminfo();
    read_interrupts();
    
    return 0;
}