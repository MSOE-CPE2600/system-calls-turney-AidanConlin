/**********************************************
*  Filename: info.c
*  Description: A file designed to print out basic information 
*  about the device that is being used to run the program.
*
*  Author: Aidan Conlin
*  Class: CPE 2600 121
*  Date: 12/8/2024
*  Note: gcc -o info info.c -Wall -Wextra
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <time.h>

/**
 * @brief Prints the current system time in seconds and nanoseconds.
 *
 * Uses `clock_gettime` to retrieve the current time and converts it to 
 * seconds and nanoseconds before displaying the result.
 */
void print_current_time() {
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        perror("Unable to access system time");
        return;
    }
    printf("Current Time (seconds): %ld\n", ts.tv_sec);
    printf("Current Time (nanoseconds): %ld\n", (long)(ts.tv_sec * 1e9 + ts.tv_nsec));
}

/**
 * @brief Prints information about the system's hardware and OS.
 *
 * Retrieves data using `uname` to display the system's network name,
 * OS name, release version, OS version, and hardware architecture.
 */
void print_system_info() {
    struct utsname sys_info;
    if (uname(&sys_info) == 0) {
        printf("System Network Name: %s\n", sys_info.nodename);
        printf("Operating System: %s\n", sys_info.sysname);
        printf("OS Release: %s\n", sys_info.release);
        printf("OS Version: %s\n", sys_info.version);
        printf("Hardware Type: %s\n", sys_info.machine);
    } else {
        perror("Unable to access system info");
    }
}

/**
 * @brief Prints the number of CPUs available to the system.
 *
 * Uses `sysconf` with the `_SC_NPROCESSORS_ONLN` flag to determine
 * and display the count of online processors.
 */
void print_cpu_count() {
    long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
    if (nprocs != -1) {
        printf("Number of CPUs: %ld\n", nprocs);
    } else {
        perror("Unable to count CPUs");
    }
}

/**
 * @brief Prints total and free memory information.Reads from `/proc/meminfo` 
 * to extract and display the total and available memory on the system in bytes. 
 * Ensures proper handling if the file cannot be accessed.
 */
void print_memory_info() {
    FILE *meminfo = fopen("/proc/meminfo", "r");
    if (!meminfo) {
        perror("Error opening meminfo");
        return;
    }

    char line[256];
    long total_memory = 0, free_memory = 0;

    while (fgets(line, sizeof(line), meminfo)) {
        if (strncmp(line, "MemTotal:", 9) == 0) {
            sscanf(line + 9, "%ld", &total_memory);
        } else if (strncmp(line, "MemFree:", 8) == 0) {
            sscanf(line + 8, "%ld", &free_memory);
        }
        if (total_memory && free_memory) break;
    }

    fclose(meminfo);

    if (total_memory) printf("Total Memory: %ld bytes\n", total_memory * 1024);
    if (free_memory) printf("Free Memory: %ld bytes\n", free_memory * 1024);
}

/**
 * @brief Calls helper functions to display the current system time, hardware
 * information, CPU count, and memory statistics. Then, outputs the information 
 * to the terminal in a readable format.
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return int 0 on successful execution.
 */
int main(int argc, char* argv[]) {
    printf("System Information:\n");
    print_current_time();
    print_system_info();
    print_cpu_count();
    print_memory_info();
    return 0;
}
