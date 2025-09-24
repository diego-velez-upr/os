#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

void handler(int signum) {
  pid_t pid = getpid();
  char log_file_name[64];
  sprintf(log_file_name, "worker_log_%d.txt", pid);

  FILE *log_file = fopen(log_file_name, "a");
  if (log_file == NULL) {
    perror("Could not open the log file.\n");
    exit(EXIT_FAILURE);
  }

  char *signal;
  switch (signum) {
    case SIGUSR1:
      signal = "SIGUSR1";
      break;
    case SIGUSR2:
      signal = "SIGUSR2";
      break;
    default:
      perror("Did not receive valid signal\n");
      exit(EXIT_FAILURE);
  }

  fprintf(log_file, "%s received\n", signal);

  fclose(log_file);
}

int main(void) {
  struct sigaction sa;
  sa.sa_handler = handler;

  sigaction(SIGUSR1, &sa, NULL);
  sigaction(SIGUSR2, &sa, NULL);

  while (1) {
    pause();
  }

  exit(EXIT_SUCCESS);
}
