#include "../include/functions.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

volatile sig_atomic_t parent_received_signal = 0;
volatile sig_atomic_t child_received_signal = 0;

void ChildHandler(int signo, siginfo_t *info, void *context) {
  if (signo != SIGUSR1) {
    printf("Actor did not receive a SIGUSR1 signal\n");
    return;
  }

  printf("Actor (PID: %d): Received SIGUSR1 from the Director\n", getpid());
  child_received_signal = 1;
}

void ParentHandler(int signo, siginfo_t *info, void *context) {
  if (signo != SIGUSR2) {
    printf("Director did not receive a SIGUSR2 signal\n");
    return;
  }

  printf("Director (PID: %d): Received SIGUSR2 from the Actor\n", getpid());
  parent_received_signal = 1;
}
