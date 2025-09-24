#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../include/functions.h"

char *text_to_recite =
    "To be, or not to be, that is the question: Whether 'tis nobler in the "
    "mind to suffer the slings and arrows of outrageous fortune, or to take "
    "arms against a sea of troubles, and by opposing end them.";

int main(void) {
  pid_t parent_pid = getpid();
  pid_t child_pid = fork();

  if (child_pid < 0) {
    printf("Could not create a child\n");
    return EXIT_FAILURE;
  }

  // Actor
  if (child_pid == 0) {
    struct sigaction sa;
    sa.sa_sigaction = &ChildHandler;
    sigaction(SIGUSR1, &sa, NULL);

    printf("Actor (PID: %d): I'm ready\n", getpid());

    while (child_received_signal == 0) {
      pause();
    }

    sleep(1);

    printf("Actor (PID: %d): %s\n", getpid(), text_to_recite);

    if (kill(parent_pid, SIGUSR2) == -1) {
      printf("Could not send signal to director\n");
      return EXIT_FAILURE;
    }

    printf("Actor (PID: %d): I'm finished, sending SIGUSR2 to the director\n",
           getpid());

    return EXIT_SUCCESS;
  }

  printf("Director (PID: %d): The play is about to begin\n", parent_pid);

  sleep(1);

  printf("Director (PID: %d): I'll send SIGUSR1 to the actor to start\n",
         parent_pid);
  if (kill(child_pid, SIGUSR1) == -1) {
    printf("Could not send signal to actor\n");
    return EXIT_FAILURE;
  }

  struct sigaction sa;
  sa.sa_sigaction = &ParentHandler;
  sigaction(SIGUSR2, &sa, NULL);

  while (parent_received_signal == 0) {
    pause();
  }

  waitpid(child_pid, NULL, 0);

  printf("Director (PID: %d): Okay, We're ending the play\n", parent_pid);

  return EXIT_SUCCESS;
}
