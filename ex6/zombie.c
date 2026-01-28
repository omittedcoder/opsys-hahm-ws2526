/*
    Implement a program that create new processes and turn them into zombies.
    Tip: Check the information about the processes in the proc filesystem (⟶ man 5 proc).
    
    A zombie process is a process that terminated but still has an entry in the process table
    until the parent process received a return value 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {

  // child pid
  int pid = fork();
  
  if (pid < 0) {
    // If fork() returns -1, an error happened.
    // Memory or processes table have no more free capacity.
    perror("fork() caused an error!");
    exit(EXIT_FAILURE);
  }
  
  if (pid > 0) {
    // Parent
    printf("Parent: PID=%i, PPID=%i\n", getpid(), getppid());
    printf("Child: PID=%i, PPID=%i\n", pid, getpid());
    
    // time for child process to be zombie
    //sleep(60);
    
    // wait for child process
    //int *status = NULL;
    //wait(status);
    //printf("Child(%i) -> %i", pid, *status);
    getchar();
  }
  
  if (pid == 0) {
    // Child
    //printf("Child: PID=%i, PPID=%i", getpid(), getppid());
    exit(EXIT_SUCCESS);
  }
  
  // Code here will be executed in both processes
  //exit(EXIT_SUCCESS);

}
