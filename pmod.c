/**********************************************
*  Filename: pmod.c
*  Description: This program demonstrates the use of the nice() 
*  system call to lower the process priority and the nanosleep()
*  system call to introduce a delay.
*  
*  Author: Aidan Conlin
*  Class: CPE 2600 121
*  Date: 12/8/2024
*  Note: Compile using `gcc -o pmod pmod.c -Wall -Wextra`
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

/**
 * @brief Demonstrates process priority modification and sleeping. The program reduces 
 * the current process's priority using the nice() system call. Then introduces a delay, 
 * pausing the program for 1.837 seconds. If any system call fails, an error is displayed.
 * 
 * @return int Returns 0 on success, or 1 if a system call fails.
 */
int main() {
    if (nice(10) == -1 && errno != 0) {
        perror("nice");
        return 1;
    }
    printf("Priority successfully reduced by 10.\n");

    struct timespec ts;
    ts.tv_sec = 1;
    ts.tv_nsec = 837272638;
    if (nanosleep(&ts, NULL) == -1) {
        perror("nanosleep");
        return 1;
    }

    printf("Goodbye! Process exiting.\n");
    return 0;
}
