/**********************************************
*  Filename: pinfo.c
*  Description: Retrieves and displays scheduling information
*  and priority for a given process ID or the current process.
*
*  Author: Aidan Conlin
*  Class: CPE 2600 121
*  Date: 12/8/2024
*  Note: Compile using `gcc -o pinfo pinfo.c -Wall -Wextra`
***********************************************/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sched.h>
#include <errno.h>

/**
 * @brief Maps scheduling policies to human-readable names.
 *
 * @param policy Integer representing the scheduling policy.
 *
 * @return const char* Human-readable name of the scheduling policy.
 */
const char* get_scheduler_name(int policy) {
    switch (policy) {
        case SCHED_OTHER:       return "Normal";
        case SCHED_FIFO:        return "FIFO";
        case SCHED_RR:          return "Round Robin";
        case SCHED_BATCH:       return "Batch";
        case SCHED_IDLE:        return "Idle";
        case SCHED_DEADLINE:    return "Deadline";
        default:                return "Unknown";
    }
}

/**
 * @brief Displays process scheduling information and priority.
 * If no PID is provided, the program uses the current process's PID.
 * Prints the PID, priority, and scheduling method of the specified process.
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 *
 * @return int 0 on success, 1 on failure.
 */
int main(int argc, char* argv[]) {
    pid_t pid;

    if (argc == 2) {
        pid = atoi(argv[1]);
        if (pid <= 0) {
            fprintf(stderr, "Invalid process ID.\n");
            return 1;
        }
    } else if (argc == 1) {
        pid = getpid();
    } else {
        fprintf(stderr, "Usage: %s [PID]\n", argv[0]);
        return 1;
    }

    errno = 0;
    int priority = getpriority(PRIO_PROCESS, pid);
    if (errno != 0) {
        perror("getpriority");
        return 1;
    }

    int policy = sched_getscheduler(pid);
    if (policy == -1) {
        perror("sched_getscheduler");
        return 1;
    }

    printf("Process ID: %d\n", pid);
    printf("Priority: %d\n", priority);
    printf("Scheduling Method: %s\n", get_scheduler_name(policy));

    return 0;
}
