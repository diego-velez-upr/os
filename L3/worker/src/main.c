#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  // Check if we got the message queue name passed
  if (argc != 2) {
    fprintf(stderr, "Did not receive message queue name!\n");
    exit(1);
  }

  char* message_queue = argv[1];

  // Open message queue for reading
  mqd_t queue = mq_open(message_queue, O_RDONLY);
  if (queue == (mqd_t)-1) {
    perror("mq_open");
    exit(1);
  }

  // Get messages from message queue
  char message[40];
  while (1) {
    ssize_t bytes_received = mq_receive(queue, message, 40, NULL);
    if (bytes_received == -1) {
      perror("mq_receive");
      exit(1);
    }

    int64_t number_received = atol(message);
    if (number_received == -1) {  // Received suicide signal
      break;
    } else if (number_received % 2 != 0) {
      fprintf(stderr, "PRIME FOUND %ld\n", number_received);
    } else {
      printf("Worker %d received number:%ld\n", getpid(), number_received);
    }
  }

  // Cleanup
  mq_close(queue);
  return 0;
}
