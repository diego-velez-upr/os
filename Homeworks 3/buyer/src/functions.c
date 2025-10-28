#include "../include/functions.h"
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define SHARED_MEMORY "ticket_office"
#define MIN(a,b) ((a) < (b) ? (a) : (b))

struct memory *AttachMemory() {
  // Open memory for R/W
  int fd = shm_open(SHARED_MEMORY, O_RDWR, 0666);
  if (fd == -1) {
    perror("shm_open");
    exit(EXIT_FAILURE);
  }

  // Set memory size
  if (ftruncate(fd, sizeof(struct memory)) == -1) {
    perror("ftruncate");
    exit(EXIT_FAILURE);
  }

  // Get memory pointer
  struct memory *shm_ptr = mmap(NULL, sizeof(struct memory),
                                PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (shm_ptr == MAP_FAILED) {
    perror("mmap");
    exit(EXIT_FAILURE);
  }

  return shm_ptr;
}

void *BuyTickets(void *arg) {
  struct thread_info *thread = (struct thread_info *)arg;
  struct timespec purchase_time;
  purchase_time.tv_sec = 0;
  purchase_time.tv_nsec = 100000000;

  int tickets_to_buy;
  while (thread->shm_ptr->available_tickets > 0) {
    tickets_to_buy = MIN(thread->shm_ptr->available_tickets, rand() % 5 + 1);
    printf("Buyer %d requests %d tickets\n", thread->num, tickets_to_buy);

    pthread_mutex_lock(thread->mutex);

    thread->shm_ptr->available_tickets -= tickets_to_buy;
    thread->shm_ptr->purchases_log[thread->shm_ptr->transactions] =
        tickets_to_buy;
    thread->shm_ptr->transactions += 1;
    printf("Thread %lu purchased %d tickets. Available %d\n", thread->id,
           tickets_to_buy, thread->shm_ptr->available_tickets);

    pthread_mutex_unlock(thread->mutex);
    nanosleep(&purchase_time, NULL);
  }

  return NULL;
}
