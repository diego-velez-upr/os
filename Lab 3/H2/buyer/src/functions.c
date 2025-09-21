#include "../include/functions.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define SHARED_MEMORY "ticket_office"

struct shm *AttachMemory() {
  // Open memory for R/W
  int fd = shm_open(SHARED_MEMORY, O_RDWR, 0666);
  if (fd == -1) {
    perror("shm_open");
    exit(EXIT_FAILURE);
  }

  // Set memory size
  if (ftruncate(fd, sizeof(struct shm)) == -1) {
    perror("ftruncate");
    exit(EXIT_FAILURE);
  }

  // Get memory pointer
  struct shm *shm_ptr =
      mmap(NULL, sizeof(struct shm), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (shm_ptr == MAP_FAILED) {
    perror("mmap");
    exit(EXIT_FAILURE);
  }

  return shm_ptr;
}

void BuyTickets(struct shm *shm_ptr, int tickets_to_buy) {
  if (tickets_to_buy > 5 || tickets_to_buy <= 0) {
    printf("Try again, invalid number of tickets\n");
    return;
  }

  // Si hay menos tickets de los que quieres comprar,
  // pues bebo vas a comprar todos los que quedan
  if (shm_ptr->available_tickets < tickets_to_buy) {
    tickets_to_buy = shm_ptr->available_tickets;
  }

  shm_ptr->available_tickets -= tickets_to_buy;
  shm_ptr->purchased_tickets += tickets_to_buy;
  shm_ptr->transactions++;

  printf("Company purchased %d tickets. Available:%d\n", tickets_to_buy,
         shm_ptr->available_tickets);
}
