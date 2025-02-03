#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

sem_t worker_sem;
sem_t product_sem;
sem_t bilanz_sem;
int bilanzsumme = 0;

void *Daniel(void *arg);
void *Christian(void *arg);
void *Lukas(void *arg);
void hire_Lukas();
void produce_good();
void sell_good();

void init() {
    sem_init(&worker_sem, 0, 35);
    sem_init(&product_sem, 0, 0);
    sem_init(&bilanz_sem, 0, 1);
}

// ---------------------------------------------
//* Important Bookmark

void *Daniel() {
    while(true) {
        sem_wait(&product_sem);
        sell_good();
        sem_wait(&bilanz_sem);
        bilanzsumme += 15;
        printf("[Daniel] Sold product. New balance: %d\n", bilanzsumme);
        sem_post(&bilanz_sem);
    }
    return NULL;
}

void *Christian() {
    while(1) {
        sem_wait(&worker_sem);
        hire_Lukas();
    }
    return NULL;
}

void *Lukas() {
    while (random() % 100 != 0) {
        sem_wait(&bilanz_sem);
        bilanzsumme -= 5;
        printf("[Lukas] Produced good. New balance: %d\n", bilanzsumme);
        sem_post(&bilanz_sem);
        produce_good();
        sem_post(&product_sem);
    }
    printf("[Lukas] Quitting...\n");
    sem_post(&worker_sem);
    return NULL;
}

//* Important Bookmark
// ---------------------------------------------
void hire_Lukas() {
    pthread_t worker_thread;
    pthread_create(&worker_thread, NULL, Lukas, NULL);
    pthread_detach(worker_thread);
    printf("[Christian] Hired a new Lukas.\n");
}

void produce_good() {
    sleep(10);  // Simulating work time
    printf("[Lukas] Finished producing a good.\n");
}

void sell_good() {
    sleep(10);  // Simulating selling time
    printf("[Daniel] Sold a product.\n");
}

int main() {
    srand(time(NULL));
    init();

    pthread_t daniel_thread, christian_thread;

    pthread_create(&daniel_thread, NULL, Daniel, NULL);
    pthread_create(&christian_thread, NULL, Christian, NULL);

    pthread_join(daniel_thread, NULL);
    pthread_join(christian_thread, NULL);

    return 0;
}
