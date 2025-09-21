#ifndef INCLUDE_FUNCTIONS_H_
#define INCLUDE_FUNCTIONS_H_

struct shm {
    int available_tickets;
    int purchased_tickets;
    int transactions;
};

struct shm* AttachMemory();

void BuyTickets(struct shm*, int);

#endif  // INCLUDE_FUNCTIONS_H_
