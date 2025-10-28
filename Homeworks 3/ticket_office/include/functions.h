#ifndef TICKET_OFFICE_INCLUDE_FUNCTIONS_H_
#define TICKET_OFFICE_INCLUDE_FUNCTIONS_H_

#define SHARED_MEMORY "ticket_office"

struct memory {
  int available_tickets;
  int purchases_log[100];
  int transactions;
};

void PrintReport(struct memory *);
struct memory *InitMemory();

#endif  // TICKET_OFFICE_INCLUDE_FUNCTIONS_H_
