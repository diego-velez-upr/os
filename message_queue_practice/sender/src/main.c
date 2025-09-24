#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  // Delete message queue in case there was something left in it
  // If was already deleted, then fails with ENOENT error
  int deleted = mq_unlink("/dvt_queue");
  if (deleted == -1 && errno != ENOENT) {
    perror("mq_unlink");
    exit(1);
  }
  printf("Message queue deleted!\n");

  // Create message queue
  struct mq_attr attr;
  attr.mq_flags = 0;
  attr.mq_maxmsg = 5;
  attr.mq_msgsize = 256;
  attr.mq_curmsgs = 1;

  mqd_t queue = mq_open("/dvt_queue", O_WRONLY | O_CREAT, 0664, &attr);
  if (queue == (mqd_t)-1) {
    perror("mq_open");
    exit(1);
  }

  // Send five messages
  char message[256] = "dimelo loco";
  int times = 0;
  while (times < 5) {
    int received = mq_send(queue, message, strlen(message) + 1, 0);
    if (received == -1) {
      perror("mq_send");
      exit(1);
    }

    printf("Message sent successfully!\n");
    times++;
    sleep(1);
  }

  // Close connection to message queue
  mq_close(queue);
  return 0;
}
