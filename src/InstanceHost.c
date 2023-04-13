/**
 * Implementation of Instance Host - simulates a cloud like environment
 *
 * Completion Time: 13 hours
 *
 * @author Edgar Hakobyan
 * @version 1.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../headers/InstanceHost.h" // CHANGE


// DATA STRUCTURES
///////////////////////////////////////////////////////////

struct host {
    pthread_t *threads;
    int numThreads;

};

// FUNCTIONS
///////////////////////////////////////////////////////////

void *runner(void *param) {
    pthread_exit(0);
}

pthread_mutex_t *lock;

/**
 * Creates host environment
 * @return
 */
host *host_create() {
    host *h = (struct host *) malloc(sizeof(host));
    pthread_t *t = (pthread_t *) malloc(sizeof(pthread_t));

    h->numThreads = 0;
    h->threads = t;
    return h;
}

/**
 * Destroys host environment
 * @param h
 */
void host_destroy(host **h) {
    free((*h)->threads);
    free(*h);
    *h = NULL;
}

/**
 * Creates new server to handle item processing in a batch.
 * @param h
 * @param batch
 */
void host_request_instance(host *h, struct job_node *batch) {
    printf("\nLoadBalancer: Received batch and spinning up new instance.\n\n");

    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);
//    pthread_t tid;
//    pthread_attr_t attr;

    struct job_node *node = batch;
    while (node != NULL) {
        pthread_t tid;
        pthread_create(&tid, NULL, runner, (void *) node->data);
        pthread_join(tid, NULL);

//    while(batch->next != NULL) {
//        pthread_create(&tid, &attr, runner, (void*)batch->data);
//        pthread_join(tid, NULL);
//    }
//
        node->data_result = (int *) malloc(sizeof(int));
        *(node->data_result) = (*(int *) node->data) * (*(int *) node->data);
//    batch->data_result = (int *) (batch->data * batch->data);
        node = node->next;
    }

    pthread_mutex_destroy(&lock);
    host_destroy(&h);
//    free(lock);
}

