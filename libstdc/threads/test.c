#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <threads.h>

#ifndef NUM_THREADS
#define NUM_THREADS 4
#endif

void *printHello(void *thr_id) {
    long tid;
    tid = (long)thr_id;
    printf("Hello There! thread #%ld, pthread ID - %lu\n", tid, thrd_current());
    thrd_exit(EXIT_SUCCESS);
}

int main(int argc, char const *argv[]) {
    thrd_t threads[NUM_THREADS];
    int rc;
    long t;

    for (t = 0; t < NUM_THREADS; t++) {
        rc = thrd_create(&threads[t], (thrd_start_t) printHello, (void *)t);
        if (rc == thrd_error) {
            printf("ERORR; thrd_create() call failed\n");
            exit(EXIT_FAILURE);
        }
    }
    thrd_exit(EXIT_SUCCESS);

}
