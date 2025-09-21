#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include "../include/functions.h"

int main(void) {
    struct shm *shm_ptr = AttachMemory();

    int tickets_to_buy;
    while (shm_ptr->available_tickets > 0) {
        printf("How many tickets do you want?\n");
        scanf("%d", &tickets_to_buy);
        BuyTickets(shm_ptr, tickets_to_buy);
        sleep(2);
    }

    munmap(shm_ptr, sizeof(struct shm));

    exit(EXIT_SUCCESS);
}
