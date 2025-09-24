#include <errno.h>
#include <mqueue.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  char* message_queue = "/prime_queue";

  // Child 1
  pid_t child1_pid = fork();
  if (child1_pid < 0) {
    perror("fork");
    exit(1);
  }

  if (child1_pid == 0) {
    execlp("./worker", "worker", message_queue, (char*)NULL);
    exit(0);
  }

  // Child 2
  pid_t child2_pid = fork();
  if (child2_pid < 0) {
    perror("fork");
    exit(1);
  }

  if (child2_pid == 0) {
    execlp("./worker", "worker", message_queue, (char*)NULL);
    exit(0);
  }

  // Delete message queue in case there was something left in it
  // If was already deleted, then fails with ENOENT error
  int deleted = mq_unlink(message_queue);
  if (deleted == -1 && errno != ENOENT) {
    perror("mq_unlink");
    exit(1);
  }

  // Create message queue
  struct mq_attr attr;
  attr.mq_flags = 0;
  attr.mq_maxmsg = 5;
  attr.mq_msgsize = 40;
  attr.mq_curmsgs = 5;

  mqd_t queue = mq_open(message_queue, O_WRONLY | O_CREAT, 0664, &attr);
  if (queue == (mqd_t)-1) {
    perror("mq_open");
    exit(1);
  }

  // Read numbers
  FILE* numbers_file = fopen("./numbers.txt", "r");
  if (numbers_file == NULL) {
    perror("fopen");
    exit(1);
  }

  // Send numbers to message queue
  char line[40];
  while (fgets(line, sizeof(line), numbers_file)) {
    int was_received = mq_send(queue, line, strlen(line) + 1, 0);
    if (was_received == -1) {
      perror("mq_send");
      exit(1);
    }
  }
  fclose(numbers_file);

  // Send suicide signal to workers
  sleep(1);
  int was_received;
  was_received = mq_send(queue, "-1", 3, 0);
  if (was_received == -1) {
    perror("mq_send");
    exit(1);
  }
  was_received = mq_send(queue, "-1", 3, 0);
  if (was_received == -1) {
    perror("mq_send");
    exit(1);
  }


  // Wait for children to kill themselves to cleanup
  waitpid(child1_pid, NULL, 0);
  waitpid(child2_pid, NULL, 0);

  mq_close(queue);
  mq_unlink(message_queue);

  return 0;
}
