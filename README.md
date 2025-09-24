# Operating System Labs and Homeworks

## Table of Contents

- [Signals](#signals)
- [Message Queues](#message-queues)
- [Shared Memory](#shared-memory)
- [How to Run](#how-to-run)

## Signals

### Sending signal

Use `kill`.
```c
#include <signal.h>

pid_t other_process = ...;
if (kill(other_process, SIGUSR1) == -1) {
  // error sending signal
}
```

### Handling Signal

```c
#include <signal.h>
#include <unistd.h>  // for pause

void gestionador(int signum) {
}

struct sigaction sa;
sa.sa_handler = gestionador;
sigaction(SIGINT, &sa, NULL);

pause()  // si quieres sleep until receiving a signal.
```

## Message Queues

### Sender

```c
#include <mqueue.h>
#include <fcntl.h>  // for O_CREAT, etc.
#include <string.h>  // for strlen

// Delete before using in case it exists with old values
int deleted = mq_unlink("/dvt_queue");
if (deleted == -1 && errno != ENOENT) {  // throws ENOENT when it doesn't exist
  // error deleting
}

struct mq_attr attr;
attr.mq_flags = 0;
attr.mq_maxmsg = 5;
attr.mq_msgsize = 256;
attr.mq_curmsgs = 1;

mqd_t queue = mq_open("/dvt_queue", O_WRONLY | O_CREAT, 0664, &attr);
if (queue == (mqd_t)-1) {
  perror("mq_open");
  exit(1);
}

char message[256] = "dimelo loco";
int received = mq_send(queue, message, strlen(message) + 1, 0);

mq_close(queue);
```

### Receiver

```c
#include <mqueue.h>
#include <fcntl.h>
#include <sys/types.h>  // for ssize_t
#include <unistd.h>  // for NULL

mqd_t queue = mq_open("/dvt_queue", O_RDONLY);
if (queue == (mqd_t)-1) {
  // error opening message queue
}

char message[256];
ssize_t bytes_received = mq_receive(queue, message, 256, NULL);
if (bytes_received == -1) {
  // error receiving message
}

// Close and delete message queue
mq_close(queue);
mq_unlink("/dvt_queue");
```

## Shared Memory

### Main Process Setup

```c
#include <sys/mman.h>
#include <fcntl.h>

// Create shared memory
int fd = shm_open("shared", O_CREAT | O_RDWR, 0666);
if (fd == -1) {
  // could not create shared memory space
}

// Set size of shared memory
if (ftruncate(fd, sizeof(struct shm)) == -1) {
  // could not set the size of the shared memory space
}

// Get pointer to shared memory
struct shm *shm_ptr =
    mmap(NULL, sizeof(struct shm), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
if (shm_ptr == MAP_FAILED) {
  // could not get a pointer to the shared memory space
}

munmap(shm_ptr, sizeof(struct shm));
shm_unlink("shared");
```

### Secondary Process

```c
#include <sys/mman.h>
#include <fcntl.h>

// Open memory for R/W
int fd = shm_open("shared", O_RDWR, 0666);
if (fd == -1) {
  // Could not open shared memory space
}

// Set memory size
// yo creo que esto no es necesario
if (ftruncate(fd, sizeof(struct shm)) == -1) {
  // could not set memory size
}

// Get memory pointer
struct shm *shm_ptr =
    mmap(NULL, sizeof(struct shm), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
if (shm_ptr == MAP_FAILED) {
  // could not get shared memory pointer
}

munmap(shm_ptr, sizeof(struct shm));
```

## How to run

```shell
cd build
cmake -S . -G "Unix Makefiles" -B build
make -C build
./build/main
```
