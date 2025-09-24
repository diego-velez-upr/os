#ifndef INCLUDE_FUNCTIONS_H_
#define INCLUDE_FUNCTIONS_H_

#define SHARED_MEMORY "ticket_office"

struct shm {
  int available_tickets;
  int purchased_tickets;
  int transactions;
};

void PrintReport(struct shm *);
struct shm *InitMemory();

#endif // INCLUDE_FUNCTIONS_H_
