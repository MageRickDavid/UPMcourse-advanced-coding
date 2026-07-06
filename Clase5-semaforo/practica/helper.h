/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 02:58:23 by rortiz            #+#    #+#             */
/*   Updated: 2026/07/06 19:27:45 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_H_
# define HELPER_H_
#include <sys/ipc.h>
#include <sys/shm.h>

#define CLAVE_MESSSAGE	((key_t) 1001)
#define CLAVE_SEMAPHORE  ((key_t) 1000)
#define EMPTY_NUMBER 0
#define OCCUPIED_NUMBER 1
#define BUFFER_SIZE 5
#define SEM_EMPTY_PRODUCER 0
#define SEM_FULL_CONSUMER 1
#define SEM_MUTEX 2
#define SEM_WAIT -1
#define SEM_SIGNAL 1


//The structure for the sharedMemory
typedef struct sharedMemory 
{
  int   buffer[BUFFER_SIZE];
  int   in;
  int   out;  
} t_custom_buffer;

int     memory_creator_finder(key_t key, size_t memory_size);
int     close_shared_memory(int memory_id);
int     semaphore_creator_finder(key_t key, int semaphore_number);
void    producing_number(int memory_id);
void    consuming_number(int memory_id);
void    initialize_buffer(int memory_id);
void    semaphore_operation(int semaphore_id, unsigned short semaphore_number, short operation);
void    print_buffer(t_custom_buffer *buffer);
void    consumer_code(int memory_id, int semaphore_id);
void    producer_code(int memory_id, int semaphore_id);
#endif