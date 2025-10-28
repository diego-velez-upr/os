#include "../include/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

int main(void) {
  struct memory *shm_ptr = InitMemory();

  shm_ptr->available_tickets = 100;
  shm_ptr->transactions = 0;

  while (shm_ptr->available_tickets > 0) {
    PrintReport(shm_ptr);
    printf("\n");

    sleep(1);
  }

  PrintReport(shm_ptr);
  printf("SOLD OUT...\n");

  munmap(shm_ptr, sizeof(struct memory));
  shm_unlink(SHARED_MEMORY);

  exit(EXIT_SUCCESS);
}
