/*
    Implement a program that create new processes and turn them into zombies.
    Tip: Check the information about the processes in the proc filesystem (⟶ man 5 proc).
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {

  int pid = fork();
  
  if (pid < 0) {
    // If fork() returns -1, an error happened.
    // Memory or processes table have no more free capacity.
    perror("\n fork() caused an error!");
    exit(EXIT_FAILURE);
  }
  
  if (pid > 0) {
    // If fork() returns a positive number, we are in the parent process.
    // The return value is the PID of the newly created child process.
    printf("\n Parent: PID=%i, PPID=%i", getpid(), getppid());
  }
  
  if (pid == 0) {
    // If fork() returns 0, we are in the child process.
    printf("\n Child: PID=%i, PPID=%i", getpid(), getppid());
  }
  
  // Code here will be executed in both processes
  exit(EXIT_SUCCESS);

}