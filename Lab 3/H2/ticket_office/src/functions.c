#include "../include/functions.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

void PrintReport(struct shm *shm_ptr) {
  printf("TICKET REPORT:\n");
  printf("Purchased tickets:%d\n", shm_ptr->purchased_tickets);
  printf("Available tickets:%d\n", shm_ptr->available_tickets);
  printf("Transactions:%d\n", shm_ptr->transactions);
}

struct shm *InitMemory() {
  // Create shared memory
  int fd = shm_open(SHARED_MEMORY, O_CREAT | O_RDWR, 0666);
  if (fd == -1) {
    perror("shm_open");
    exit(EXIT_FAILURE);
  }

  // Set size of shared memory
  if (ftruncate(fd, sizeof(struct shm)) == -1) {
    perror("ftruncate");
    exit(EXIT_FAILURE);
  }

  // Get pointer to shared memory
  struct shm *shm_ptr =
      mmap(NULL, sizeof(struct shm), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (shm_ptr == MAP_FAILED) {
    perror("mmap");
    exit(EXIT_FAILURE);
  }

  return shm_ptr;
}
