/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 02:18:49 by rortiz            #+#    #+#             */
/*   Updated: 2026/03/28 10:07:40 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

/**
 * @brief Creates or finds a shared memory based on its key.
 * @param {key_t} key: The key of the shared memory
 * @return {int} shared memory id upon successful creation, -1 otherwise
 */
int	memory_creator_finder(key_t key, size_t memory_size)
{
	int memory_id;
	
	memory_id = shmget(key, memory_size, IPC_CREAT | 0666);
	if (memory_id < 0)
	{
		perror("Error creating the shared memory\n");
		exit(EXIT_FAILURE);
	}
	return (memory_id);
}

/**
 * @brief Sends a message to the designated shared memory
 * @param {int} memory_id: The id of the shared memory.
 * @param {unsigned char} number: The number to send.
 * @param {unsigned char} my_turn: The current turn.
 * @param {unsigned char} other_turn: The other player turn.
 */
void sending_message(int memory_id, unsigned char number, unsigned char my_turn, unsigned char other_turn)
{
	NUMBER_MESSAGE	*shared_memory;
	char			message[100];

	if (my_turn == GUESSER)
		strcpy(message, "GUESSER");
	else
		strcpy(message, "OTHER"); 
	shared_memory = (NUMBER_MESSAGE*)shmat(memory_id, 0, 0);
	if (shared_memory->turn == my_turn)
	{
		printf("%s", message);
		printf(" is sending: %d\n", number);
		shared_memory->number = number;
		shared_memory->turn = other_turn;	
	}
}

/**
 * @brief Receives a message from the shared memory
 * @param {int} memory_id: The id of the shared memory.
 * @param {unsigned char} my_turn: The current turn 
 * @return {int} The number received, -1 otherwise there is not a message yet to receive
 */
int	receiving_message(int memory_id, unsigned char my_turn)
{
	NUMBER_MESSAGE	*shared_memory;
	char			message[100];

	if (my_turn == GUESSER)
		strcpy(message, "GUESSER");
	else
		strcpy(message, "OTHER"); 
	shared_memory = (NUMBER_MESSAGE*)shmat(memory_id, 0, 0);
	if (shared_memory->turn == my_turn)
	{
		printf("%s", message);
		printf(" is receiving the number: %d\n", shared_memory->number);
		return ((int)shared_memory->number);
	}
	else
		return (-1);
}

/**
 * @brief Closes the shared memory
 * @param {int} memory_id: The id of the shared memory we want to close
 * @return {int} Returns 0 if successfully closed, -1 otherwise
 */
int	close_shared_memory(int memory_id)
{
	int ret;
	
	ret = shmctl(memory_id,IPC_RMID, (void*)0);
	if (ret < 0)
	{
		perror("Error closing shared memory");
		exit(EXIT_FAILURE);
	}
	return (ret);
}

/**
 * @brief Generates a random number in between a max and minimum range
 * @param {int} max_number: The maximum number in the range.
 * @param {int} min_number: The minimum number in the range.
 * @return {int} The random number.
 */
int	generate_random_number(int max_number, int min_number)
{
	return ((rand() % ((max_number - min_number) + 1)) + min_number);
}
