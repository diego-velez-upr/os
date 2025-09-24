#ifndef INCLUDE_FUNCTIONS_H_
#define INCLUDE_FUNCTIONS_H_

#include <signal.h>

extern volatile sig_atomic_t parent_received_signal;
extern volatile sig_atomic_t child_received_signal;

void ParentHandler(int signo, siginfo_t *info, void *context);
void ChildHandler(int signo, siginfo_t *info, void *context);

#endif  // INCLUDE_FUNCTIONS_H_
