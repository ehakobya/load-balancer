/**
 * Implementation of Instance Host - simulates a cloud like environment
 *
 * Completion Time: 13 hours
 * @author Edgar Hakobyan
 * @version 1.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "InstanceHost.h" // CHANGE


// DATA STRUCTURES
///////////////////////////////////////////////////////////

struct host {
    pthread_t *threads;
    pthread_mutex_t lock;
//    int numThreads;
};

//pthread_mutex_t *lock;

// FUNCTIONS
///////////////////////////////////////////////////////////

void *runner(void *param) {
//    struct job_node *node = batch;
//    while (node != NULL) {
//        pthread_t tid;
//        pthread_create(&tid, NULL, runner, (void *) node->data);
//        pthread_join(tid, NULL);
//    }
    struct job_node *batch = (struct job_node *) param;
    while (batch->next) {
        int data_result = batch->data * batch->data;
        *batch->data_result = data_result;
        batch = batch->next;
    }
//    node->data_result = (int *) malloc(sizeof(int));
//    *(node->data_result) = (*(int *) node->data) * (*(int *) node->data);
//    node = node->next;
}


/**
 * Creates host environment
 * @return
 */
host *host_create() {
    host *h = (struct host *) malloc(sizeof(h));
    pthread_mutex_init(&h->lock, NULL);
    return h;
}

/**
 * Destroys host environment
 * @param h
 */
void host_destroy(host **h) {
    struct host *pHost = *h;
    pthread_mutex_destroy(&pHost->lock);
    free(*h);
//    free((*h)->threads);
    *h = NULL;
}

/**
 * Creates new server to handle item processing in a batch.
 * @param h
 * @param batch
 */
void host_request_instance(host *h, struct job_node *batch) {
    printf("\nLoadBalancer: Received batch and spinning up new instance.\n\n");

//    pthread_t tid;
//    pthread_mutex_t lock;
    pthread_mutex_lock(&h->lock);
    pthread_t *thread = (pthread_t *) malloc(sizeof(pthread_t));
    pthread_create(thread, NULL, runner, (void *) batch);
//    pthread_mutex_init(&lock, NULL);
    pthread_join(*thread, NULL);
    pthread_mutex_unlock(&h->lock);


//    while(batch->next != NULL) {
//        pthread_create(&tid, &attr, runner, (void*)batch->data);
//        pthread_join(tid, NULL);
//    }

//    pthread_mutex_destroy(&lock);
//    host_destroy(&h);
//    free(lock);
}
