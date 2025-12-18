/*
    In this assignment, you will write a little application to launch another program and
    measure its CPU runtime.

    Basic functionality when user executes your program mytime:
        1. If no command line arguments are given, the program should print information on
            how to call the program correctly.
        2. When executed with at least one command line argument the first argument should
            be interpreted as a program name. Your program should then execute this program –
            as a separate process – and pass all remaining command line arguments as arguments
            to the executed program.
        3. For any executed program its return value and the CPU time of the process in
            milliseconds should be printed.
        4. You must create a Makefile such that when someone types make in your working
            directory it will compile the program with an output of mytime.

    Tip: You will need the system commands fork, a version of exec, waitpid, and
        clock_gettime to complete this task. For details on how to use these, you can use
        UNIX’s man pages. There is also an online version at https://www.kernel.org/doc/man-pages/.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <bits/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

enum { NS_PER_MS = 1000000 };

int main(int argc, char *argv[]) {

    // when no parameters then print usage
    if(argc < 2) {
        printf("mytime [PROGRAM] <ARGS OF PROGRAM>");
        exit(EXIT_FAILURE);
    }

    // fork
    int pid = fork();
    if (pid < 0) {
        // If fork() returns -1, an error happened.
        // Memory or processes table have no more free capacity.
        perror("\n fork() caused an error!");
        exit(EXIT_FAILURE);
    }

    // If PID!=0 --> Parent process
    if (pid) {

    }
    // If PID=0 --> Child process
    else {
        // parse arguments
        char *prog = argv[1];
        char **args = argv + 2;

        // print arguments
        // printf("%s\n", prog);
        // for(int i = 0; i < (argc - 2); i++) {
        //     printf("%s\n", args[i]);
        // }

        // Current program is replaced by prog
        // prog will be the process name in the process table
        execvp(prog, args);
    }

    struct timespec cpu_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpu_time);
    printf("%d.%.9ld\n", (int)cpu_time.tv_sec, cpu_time.tv_nsec);

    exit(EXIT_SUCCESS);
}