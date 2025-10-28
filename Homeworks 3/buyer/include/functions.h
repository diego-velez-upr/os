#ifndef BUYER_INCLUDE_FUNCTIONS_H_
#define BUYER_INCLUDE_FUNCTIONS_H_

#include <pthread.h>

struct memory {
  int available_tickets;
  int purchases_log[100];
  int transactions;
};

struct thread_info {
  pthread_t id;
  int num;
  pthread_mutex_t *mutex;
  struct memory *shm_ptr;
};

struct memory *AttachMemory();

void *BuyTickets(void *);

#endif // BUYER_INCLUDE_FUNCTIONS_H_
