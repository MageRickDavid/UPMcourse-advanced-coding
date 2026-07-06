/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 04:56:52 by rortiz            #+#    #+#             */
/*   Updated: 2026/07/06 20:17:09 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

/**
 * @brief Creates or finds a shared memory based on its key.
 * @param {key_t} key: The key of the shared memory
 * @return {int} shared memory id upon successful creation, -1 otherwise
 */
int memory_creator_finder(key_t key, size_t memory_size)
{
	int memory_id;
	
	memory_id = shmget(key, memory_size, IPC_CREAT | 0666);
	if (memory_id < 0)
	{
		perror("Error creating the shared memory");
		exit(EXIT_FAILURE);
	}
	return (memory_id);
}

/**
 * @brief Creates a semaphore or finds one that already exists.
 * @param {key_t} key: The key of the semaphore.
 * @return {int} semaphore id upon successful creation, -1 otherwise
 */
int semaphore_creator_finder(key_t key, int semaphore_number)
{
    int     semid;
    
    semid = semget(key, semaphore_number, IPC_CREAT | 0600);
    if (semid == -1)
    {
        perror("Error creating the semaphores");
        exit(EXIT_FAILURE);
    }
    return (semid); 
}

/**
 * @brief Produces a number and places it at a designated shared memory
 * @param {int} memory_id: The id of the shared memory.
 */
void    producing_number(int memory_id)
{
	t_custom_buffer	*shared_memory;
    int             current_in;

	shared_memory = (t_custom_buffer*)shmat(memory_id, 0, 0);
	current_in = shared_memory -> in;
    if (shared_memory->buffer[current_in] != EMPTY_NUMBER)
    {
        perror("Error producer tried to place a number at an occupied cell");
        exit(EXIT_FAILURE);
    }
    printf("Producing the number: %d ", OCCUPIED_NUMBER);
    printf("and placing it at the position: %d\n", current_in);
	shared_memory -> buffer[current_in] = OCCUPIED_NUMBER;
    shared_memory -> in = (current_in + 1) % BUFFER_SIZE;
    printf("Producer moved position to: %d\n", shared_memory->in);
    printf("Printing from producer\n");
    print_buffer(shared_memory);
}

/**
 * @brief Consumes a number from a designated shared memory
 * @param {int} memory_id: The id of the shared memory.
 */
void    consuming_number(int memory_id)
{
	t_custom_buffer	*shared_memory;
    int             current_out;

	shared_memory = (t_custom_buffer*)shmat(memory_id, 0, 0);
	current_out = shared_memory -> out;
    if (shared_memory->buffer[current_out] != OCCUPIED_NUMBER)
    {
        perror("Error consumer tried to consume a number from an empty cell");
        exit(EXIT_FAILURE);
    }
    printf("Consuming and placing: %d ", EMPTY_NUMBER);
    printf("and removing it from the position: %d\n", current_out);
	shared_memory -> buffer[current_out] = EMPTY_NUMBER;
    shared_memory -> out = (current_out + 1) % BUFFER_SIZE;
    printf("Printing from consumer\n");
    print_buffer(shared_memory);
}

/**
 * @brief Fills the shared memory with the corresponding values
 * @param {int} memory_id: Identification of the shared memory.
 */
void    initialize_buffer(int memory_id)
{
	int             i;
    t_custom_buffer *buffer;

	i = 0;
    buffer = (t_custom_buffer*)shmat(memory_id, 0, 0);
	while (i < BUFFER_SIZE)
	{
		buffer->buffer[i] = 0;
		i++;
	}
	buffer->in = 0;
	buffer->out = 0;
}

/**
 * @brief Handles the producer
 * @param {int} memory_id: The id of the shared memory
 * @param {int} semaphore_id: The id of the semaphore
 */
void	producer_code(int memory_id, int semaphore_id)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		semaphore_operation(semaphore_id, SEM_EMPTY_PRODUCER, SEM_WAIT);
		semaphore_operation(semaphore_id, SEM_MUTEX, SEM_WAIT);
		producing_number(memory_id);
		semaphore_operation(semaphore_id, SEM_MUTEX, SEM_SIGNAL);
		semaphore_operation(semaphore_id, SEM_FULL_CONSUMER, SEM_SIGNAL);
		i++;
	}
}

/**
 * @brief Handles the consumer
 * @param {int} memory_id: The id of the shared memory
 * @param {int} semaphore_id: The id of the semaphore
 */
void	consumer_code(int memory_id, int semaphore_id)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		semaphore_operation(semaphore_id, SEM_FULL_CONSUMER, SEM_WAIT);
		semaphore_operation(semaphore_id, SEM_MUTEX, SEM_WAIT);
		consuming_number(memory_id);
		semaphore_operation(semaphore_id, SEM_MUTEX, SEM_SIGNAL);
		semaphore_operation(semaphore_id, SEM_EMPTY_PRODUCER, SEM_SIGNAL);
		i++;
	}
}

/**
 * @brief Handles the semaphore operations
 * @param {int} semaphore_id: id of the semaphore.
 * @param {unsigned short} semaphore_number: The number of the semaphore on which to perform the operation
 * @param {short} operation: Which operation to perform, Either wait or signal
 */
void	semaphore_operation(int semaphore_id, unsigned short semaphore_number, short operation)
{
	struct sembuf	sem_operation;

	sem_operation.sem_num = semaphore_number;
	sem_operation.sem_op = operation;
	sem_operation.sem_flg = 0;
	if (semop(semaphore_id, &sem_operation, 1) == -1)
	{
		perror("Semop failed");
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Prints the bytes inside the buffer
 * @param {t_custom_buffer*} buffer: Memory space from where to print bytes.
 */
void    print_buffer(t_custom_buffer *buffer)
{
    int     i;
    char    c;

    i = 0;
    while (i < BUFFER_SIZE)
    {
        c = buffer->buffer[i] + '0';
        write(1, &c, 1);
        i++;
    }
    write(1, "\n", 1);
}



