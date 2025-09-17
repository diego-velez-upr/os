#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  // Open message queue for reading
  mqd_t queue = mq_open("/dvt_queue", O_RDONLY);
  if (queue == (mqd_t)-1) {
    perror("mq_open");
    exit(1);
  }

  // Read five messages
  char message[256];
  int times = 0;
  while (times < 5) {
    ssize_t bytes_received = mq_receive(queue, message, 256, NULL);
    if (bytes_received == -1) {
      perror("mq_receive");
      exit(1);
    }

    printf("Received message:%s\n", message);
    times++;
  }

  // Close and delete message queue
  mq_close(queue);
  mq_unlink("/dvt_queue");
  return 0;
}
