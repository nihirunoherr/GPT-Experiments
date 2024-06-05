#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <sys/utsname.h>

// Function to get the operating system information
void getOSInfo() {
    FILE *fp;
    char buffer[128];

    fp = fopen("/etc/os-release", "r");
    if (fp == NULL) {
        perror("Failed to open /etc/os-release");
        return;
    }

    printf("Operating System: ");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strncmp(buffer, "PRETTY_NAME=", 12) == 0) {
            buffer[strlen(buffer) - 1] = '\0'; // Remove the newline character
            printf("%s\n", buffer + 13);
            break;
        }
    }

    fclose(fp);
}

// Function to get the kernel version
void getKernelVersion() {
    struct utsname unameData;
    if (uname(&unameData) == 0) {
        printf("Kernel Version: %s\n", unameData.release);
    } else {
        perror("uname");
    }
}

// Function to get the CPU information
void getCPUInfo() {
    FILE *fp;
    char buffer[128];
    char *model = NULL;

    fp = fopen("/proc/cpuinfo", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/cpuinfo");
        return;
    }

    printf("CPU: ");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strncmp(buffer, "model name\t: ", 13) == 0) {
            model = strdup(buffer + 13);
            model[strlen(model) - 1] = '\0'; // Remove the newline character
            printf("%s\n", model);
            free(model);
            break;
        }
    }

    fclose(fp);
}

// Function to get the memory information
void getMemoryInfo() {
    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        printf("Memory: %ld MB total, %ld MB free\n", info.totalram / (1024 * 1024), info.freeram / (1024 * 1024));
    } else {
        perror("sysinfo");
    }
}

// Function to get the disk usage
void getDiskInfo() {
    FILE *fp;
    char buffer[128];

    fp = popen("df -h --output=source,fstype,size,used,avail,pcent,target -x tmpfs -x devtmpfs | grep '^/'", "r");
    if (fp == NULL) {
        perror("Failed to run df command");
        return;
    }

    printf("Disk Usage:\n");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    pclose(fp);
}

int main() {
    printf("System Information:\n");
    getOSInfo();
    getKernelVersion();
    getCPUInfo();
    getMemoryInfo();
    getDiskInfo();

    return 0;
}
