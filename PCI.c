// PCI.c
#include <stdio.h>
#include <dirent.h>
#include <string.h>

void scan_pci() {
    DIR *dir = opendir("/sys/bus/pci/devices");
    if (!dir) {
        printf("无法访问PCI设备信息\n");
        return;
    }
    
    struct dirent *entry;
    printf("\n=== PCI设备列表 ===\n");
    
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        
        char path[256];
        char vendor[64] = "未知";
        char device[64] = "未知";
        FILE *f;
        
        // 读取厂商ID
        sprintf(path, "/sys/bus/pci/devices/%s/vendor", entry->d_name);
        f = fopen(path, "r");
        if (f) {
            fgets(vendor, sizeof(vendor), f);
            fclose(f);
        }
        
        // 读取设备名
        sprintf(path, "/sys/bus/pci/devices/%s/device", entry->d_name);
        f = fopen(path, "r");
        if (f) {
            fgets(device, sizeof(device), f);
            fclose(f);
        }
        
        printf("设备: %s\n", entry->d_name);
        printf("  厂商: %s", vendor);
        printf("  设备号: %s", device);
        printf("\n");
    }
    
    closedir(dir);
}

int main() {
    scan_pci();
    return 0;
}