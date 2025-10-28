#include "../include/functions.h"
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <threads.h>
#include <time.h>
#include <unistd.h>

int main(void) {
  int success;
  size_t threads_to_create = 3;

  srand(time(NULL));

  // Setup memory
  struct memory *shm_ptr = AttachMemory();

  // Setup threads
  struct thread_info *threads = calloc(3, sizeof(struct thread_info));
  if (threads == NULL) {
    perror("calloc");
    exit(EXIT_FAILURE);
  }

  pthread_attr_t thread_attr;
  success = pthread_attr_init(&thread_attr);
  if (success != 0) {
    perror("pthread_attr_init");
    exit(EXIT_FAILURE);
  }

  // Setup mutex
  pthread_mutex_t mutex;
  success = pthread_mutex_init(&mutex, NULL);
  if (success != 0) {
    perror("pthread_mutex_init");
    exit(EXIT_FAILURE);
  }

  // Do work
  printf("Buy your tickets right now ...\n");
  for (size_t tnum = 0; tnum < threads_to_create; tnum++) {
    threads[tnum].num = tnum + 1;
    threads[tnum].mutex = &mutex;
    threads[tnum].shm_ptr = shm_ptr;

    success = pthread_create(&threads[tnum].id, &thread_attr, &BuyTickets,
                             &threads[tnum]);
    if (success != 0) {
      perror("pthread_create");
      exit(EXIT_FAILURE);
    }
  }

  // Destroy threads attribute object because it is no longer needed
  success = pthread_attr_destroy(&thread_attr);
  if (success != 0) {
    perror("pthread_attr_destroy");
    exit(EXIT_FAILURE);
  }

  // Wait til they finish working
  void *thread_result;  // should be NULL, so don't need to free :)
  for (size_t tnum = 0; tnum < threads_to_create; tnum++) {
    success = pthread_join(threads[tnum].id, &thread_result);
    if (success != 0) {
      perror("pthread_join");
      exit(EXIT_FAILURE);
    }
  }

  // Cleanup
  munmap(shm_ptr, sizeof(struct memory));
  pthread_mutex_destroy(&mutex);
  free(threads);

  exit(EXIT_SUCCESS);
}
