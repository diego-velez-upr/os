#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    perror("Usage: main <pid1> <pid2>\n");
    exit(EXIT_FAILURE);
  }

  pid_t pid1 = (pid_t)atoi(argv[1]);
  pid_t pid2 = (pid_t)atoi(argv[2]);

  FILE *commands_file = fopen("../test/commands.txt", "r");
  if (commands_file == NULL) {
    perror("Could not open commands file\n");
    exit(EXIT_FAILURE);
  }

  char line[256];
  while (fgets(line, sizeof(line), commands_file)) {
    // Parse command
    char worker[8];
    char signal[8];
    strncpy(worker, line, 7);
    strncpy(signal, line + 8, 7);
    worker[7] = '\0';
    signal[7] = '\0';

    // Get worker PID
    pid_t worker_pid;
    if (strcmp(worker, "worker1") == 0) {
      worker_pid = pid1;
    } else if (strcmp(worker, "worker2") == 0) {
      worker_pid = pid2;
    } else {
      perror("Invalid worker\n");
      exit(EXIT_FAILURE);
    }

    // Get signal number
    int signal_num;
    if (strcmp(signal, "SIGUSR1") == 0) {
      signal_num = SIGUSR1;
    } else if (strcmp(signal, "SIGUSR2") == 0) {
      signal_num = SIGUSR2;
    } else {
      perror("Invalid signal\n");
      exit(EXIT_FAILURE);
    }

    fprintf(stderr, "Sending %d worker the %s signal\n", worker_pid, signal);

    sleep(1);

    // Send signal
    if (kill(worker_pid, signal_num) == -1) {
      perror("Could not send signal to program\n");
      exit(EXIT_FAILURE);
    }
  }

  fclose(commands_file);

  sleep(1);

  kill(pid1, SIGKILL);
  kill(pid2, SIGKILL);

  exit(EXIT_SUCCESS);
}
