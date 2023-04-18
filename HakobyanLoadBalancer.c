/**
 * Implementation of Load Balancer
 *
 * Completion Time: 9 hours
 * @author Edgar Hakobyan
 * @version 1.0
 */
#include <stdio.h>
#include <stdlib.h>
#include "HakobyanLoadBalancer.h"
#include <pthread.h>

// DATA STRUCTURES
///////////////////////////////////////////////////////////

struct balancer {
    int batchSize;
    int numJobs;
    struct host *host;
    struct job_node *listJobs;
    pthread_mutex_t *lock;
};

int bSize;

// FUNCTIONS
///////////////////////////////////////////////////////////

/**
 * Creates load balancers and takes size of the batch
 * @param batch_size
 * @return
 */
balancer *balancer_create(int batch_size) {

    balancer *lb = (balancer *) malloc(sizeof(balancer));
    lb->listJobs = (struct job_node*)malloc(sizeof(struct job_node) * batch_size);
    lb->batchSize = batch_size;
    lb->numJobs = 0;
//    lb->listJobs = NULL;
//    lb->listJobs = (struct job_node *) malloc(sizeof(struct job_node) * batch_size);
    lb->host = host_create();

    pthread_mutex_init(&lb->lock, NULL);
    return lb;
}

/**
 * Destroys/Shuts down the load balancer
 * @param lb load balancer
 */
void balancer_destroy(balancer **lb) {

    struct balancer* loadBalancer = *lb;
//    pthread_mutex_destroy(&(*lb)->lock);
    if(loadBalancer->numJobs != 0) {
        host_request_instance(loadBalancer->host, loadBalancer->listJobs);
    }
//    host_destroy(&(*lb)->host);
    pthread_mutex_destroy(&loadBalancer->lock);
    host_destroy(&(loadBalancer->host));
    free(*lb);
    *lb = NULL;
}


/**
 * Adds job to load balancer while requesting new instance from InstanceHost.
 * @param lb load balancer
 * @param user_id user id making the request
 * @param data data to be processed
 * @param data_return pointer to a location with the results after processing
 */
void balancer_add_job(balancer *lb, int user_id, int data, int *data_return) {

    printf("LoadBalancer: Received new job from user #%d to process data=%d and store it at %p.\n", user_id, data, data_return);

    pthread_mutex_lock(&lb->lock);

    struct job_node *job = (struct job_node *) malloc(sizeof(struct job_node));
    job->data = data;
    job->data_result = data_return;
    job->next = lb->listJobs;
    job->user_id = user_id;

    lb->listJobs = job;
    lb->numJobs++;

    if (lb->numJobs == lb->batchSize) {
        host_request_instance(lb->host, lb->listJobs);
        struct job_node* temp;
//        lb->listJobs = NULL;
//        lb->numJobs = 0;
        while(lb->listJobs->next){
            free(lb->listJobs);
            lb->listJobs = lb->listJobs->next;
        }
        lb->numJobs = 0;
    }
    pthread_mutex_unlock(&lb->lock);
}