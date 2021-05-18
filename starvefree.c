#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Initialize readers count
int read_count = 0;

// Initial critical data section to be shared
long data = 1;

// Declaring semaphores
sem_t queue_mutex, write_mutex, read_mutex;

// reader function
void *reader(void *rid)
{

    // Wait in queue till other requests are serviced
    sem_wait(&queue_mutex);

    // wait till read count semaphore is available
    sem_wait(&read_mutex);

    // Incrememt read count semaphoere
    read_count++;

    // If current reader is the first reader wait till
    // other writers release the resource semaphore
    if (read_count == 1)
        sem_wait(&write_mutex);

    // Release the rw_queue semaphore for other process
    sem_post(&queue_mutex);

    // Allow other readers to modify readcount semaphore
    sem_post(&read_mutex);

    //critical section
    printf("Reader %d: read data as %ld\n", *((int *)rid), data);

    //exit section

    // Wait for read count semaphore access
    sem_wait(&read_mutex);

    // Decrement read count semaphore after reading is done
    read_count--;

    // Release resource semaphore for writer if
    // no other reader is remaining or left.
    if (read_count == 0)
        sem_post(&write_mutex);

    // Allow other readers to modify readcount semaphore
    sem_post(&read_mutex);
}

// Function to implement write functionality of shared data
void *writer(void *wid)
{
    //entery section

    // Wait in queue till other requests are serviced
    sem_wait(&queue_mutex);

    // Wait its turn to modify resource semaphore
    sem_wait(&write_mutex);

    // Release the rw_queue semaphore for other process
    sem_post(&queue_mutex);

    //critical section
    data = data *5 ;
    printf("Writer %d modified data to %ld\n", (*((int *)wid)), data);

    //exit section

    // Release the resource semaphore for next process
    sem_post(&write_mutex);
}

int main()
{
    // Initialize count of readers, writers and max of both
    int READERS, WRITERS, MAX_ID;

    // Get count of readers from user input
    printf("Enter Number of Readers: ");
    scanf("%d", &READERS);

    // Now get writers count as user input
    printf("Enter Number of Writers: ");
    scanf("%d", &WRITERS);

    // Store larger count in MAX_ID variable
    MAX_ID = READERS >= WRITERS ? READERS : WRITERS;

    // create an array and store id number in it
    int id_arr[MAX_ID];
    for (int i = 0; i < MAX_ID; i++)
        id_arr[i] = i + 1;

    // create array of threads for all readers and writers
    pthread_t read[READERS], write[WRITERS];

    // semaphore initialisation
    sem_init(&queue_mutex, 0, 1);
    sem_init(&read_mutex, 0, 1);
    sem_init(&write_mutex, 0, 1);

    for (int i = 0; i < READERS; i++)
        pthread_create(&read[i], NULL, (void *)reader, (void *)&id_arr[i]);

    // Similarly, Initialize writer thread with writer function
    for (int i = 0; i < WRITERS; i++)
        pthread_create(&write[i], NULL, (void *)writer, (void *)&id_arr[i]);

    // Join all reader threads to parent process
    for (int i = 0; i < READERS; i++)
        pthread_join(read[i], NULL);

    // Also, Join all writer threads to parent process
    for (int i = 0; i < WRITERS; i++)
        pthread_join(write[i], NULL);

    return 0;
}
