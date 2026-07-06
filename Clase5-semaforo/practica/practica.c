/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practica.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 08:12:57 by rortiz            #+#    #+#             */
/*   Updated: 2026/07/06 19:51:08 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

int main(void)
{
    int             memory_id;
    int             semaphore_id;
    pid_t           pid_producer;
    pid_t           pid_consumer;
    
    memory_id = memory_creator_finder(CLAVE_MESSSAGE, sizeof(t_custom_buffer));
    initialize_buffer(memory_id);
    semaphore_id = semaphore_creator_finder(CLAVE_SEMAPHORE, 3);
    if (semctl(semaphore_id, SEM_EMPTY_PRODUCER, SETVAL, BUFFER_SIZE) < 0)
    {
        perror("Error beginning the producer's semaphore");
        exit(EXIT_FAILURE);
    }
    if (semctl(semaphore_id, SEM_FULL_CONSUMER, SETVAL, 0) < 0)
    {
        perror("Error beginning the consumer's semaphore");
        exit(EXIT_FAILURE);
    }
    if (semctl(semaphore_id, SEM_MUTEX, SETVAL, 1) < 0)
    {
        perror("Error beginning the mutex's semaphore");
        exit(EXIT_FAILURE);
    }
    pid_producer = fork();
    if (pid_producer == 0)
    {
        printf("Producer child created!\n");
        producer_code(memory_id, semaphore_id);
        exit(EXIT_SUCCESS);   
    } 
    else if (pid_producer < 0)
    {
        perror("Creating producer child failed\n");
        exit(EXIT_FAILURE);
    }
    pid_consumer = fork();
    if (pid_consumer == 0)
    {
        printf("Consumer child created!\n");
        consumer_code(memory_id, semaphore_id);
        exit(EXIT_SUCCESS);   
    } 
    else if (pid_consumer < 0)
    {
        perror("Creating consumer child failed\n");
        exit(EXIT_FAILURE);
    }
    waitpid(pid_producer, NULL, 0);
    waitpid(pid_consumer, NULL, 0);
    if (semctl(semaphore_id, 0, IPC_RMID) == -1)
    {
    	perror("Error removing semaphore set");
    	exit(EXIT_FAILURE);
    }
    if (shmctl(memory_id, IPC_RMID, NULL) == -1)
    {
    	perror("Error removing shared memory");
    	exit(EXIT_FAILURE);
    }
    return (0);
}
