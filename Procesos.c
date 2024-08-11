#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

void print_memory_info() {
    struct sysinfo info;
    if (sysinfo(&info) != 0) {
        perror("sysinfo");
        return;
    }

    printf("Total RAM: %lu MB\n", info.totalram / 1024 / 1024);
    printf("Free RAM: %lu MB\n", info.freeram / 1024 / 1024);
}

void print_process_info() {
    pid_t pid = getpid();
    pid_t ppid = getppid();

    printf("Parent Process ID: %d\n", ppid);
    printf("Current Process ID: %d\n", pid);

    // List child processes of the current process
    DIR *dir;
    struct dirent *entry;
    char path[256];
    snprintf(path, sizeof(path), "/proc/%d/task/%d/children", pid, pid);

    FILE *file = fopen(path, "r");
    if (file) {
        printf("Child Processes of Current Process (%d):\n", pid);
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("\t%s", line);
        }
        fclose(file);
    } else {
        printf("No child processes or unable to read the process info.\n");
    }
}

int main() {
    print_memory_info();
    print_process_info();
    return 0;
}
