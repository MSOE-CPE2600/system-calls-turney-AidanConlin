# system-calls
system-calls-turney-AidanConlin created by GitHub Classroom

This collection of programs demonstrates the use of various POSIX system calls to interact with and manage system resources, processes, and files. Each program explores a specific aspect of system-level programming, including retrieving system information, querying and modifying process attributes, and managing file metadata. The programs are written in C and compiled using GCC, with a focus on clarity, proper error handling, and adherence to best practices.

Programs Included:
info.c: Displays detailed information about the system, including the current time, operating system details, number of CPUs, and memory usage, using system calls such as clock_gettime, uname, and sysconf.

pinfo.c: Retrieves and displays process information such as process ID, priority, and scheduling method, leveraging calls like getpriority and sched_getscheduler.

pmod.c: Modifies process attributes, including priority adjustment using nice, and demonstrates the use of nanosleep for precise process delays.

finfo.c: Provides detailed metadata about a file, such as size, permissions, owner, group, and last modification time, using the stat system call and related utilities

To compile: make use of the provided makefile with "make" or compile individually with 
"gcc -o (filename) (filename).c"