/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 02:18:49 by rortiz            #+#    #+#             */
/*   Updated: 2026/03/14 07:24:48 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

/**
 * @brief Creates or finds a message queue based on its key.
 * @param {key_t} key: The key of the message queue
 * @return {int} message id upon successful creation, -1 otherwise
 */
int	message_creator_finder(key_t key)
{
	int msg_id;
	
	msg_id = msgget(key, IPC_CREAT | 0666);
	if (msg_id < 0)
	{
		perror("Error creating the message\n");
		exit(EXIT_FAILURE);
	}
	return (msg_id);
}

/**
 * @brief Sends a message to the designated message queue
 * @param {int} msg_id: The id of the message queue 
 * where we will send the message.
 * @param {char*} str: Pointer to the string we want to send.
 * @param {int} type: An integer for designating the type of message we are sending
 * @return {int} 0 if the message was sent successfully, -1 otherwise
 */
int	sending_message(int msg_id, char *str, long type)
{
	int				signal;
	message_queue	message;
	
	message.mtype = type;
	strcpy(message.mtext, str);
	signal = msgsnd(msg_id, &message, strlen(message.mtext) + 1, 0);
	if (signal != 0)
	{
		perror("Error sending the message");
		exit(EXIT_FAILURE);
	}
	return (signal);
}

/**
 * @brief Receives a message
 * @param {int} msg_id: The id of the message queue 
 * from where we will receive the message.
 * @param {char[MAX_LENGTH]} buffer: Point towards the space of memory where the message will be stored.
 * @param {long} type: An integer for designating the type of message we are receiving
 * @return {int} The length of the message if received successfully, -1 otherwise
 */
int	receiving_message(int msg_id, long type, char buffer[MAX_LENGTH])
{
	ssize_t			message_len;
	message_queue	message;
	
	message_len = msgrcv(msg_id, &message, MAX_LENGTH, type, 0);
	if (message_len < 0)
	{
		perror("Error receiving message");
		exit(EXIT_FAILURE);
	}
	strcpy(buffer, message.mtext);
	return (message_len);
}

/**
 * @brief Closes message queue
 * @param {int} msg_id: The id of the message queue 
 * we want to close.
 * @return {int} Returns 0 if successfully closed, -1 otherwise
 */
int	close_queue(int msg_id)
{
	int ret;
	
	ret = msgctl(msg_id,IPC_RMID,(struct msqid_ds*)0);
	if (ret < 0)
	{
		perror("Error closing message queue");
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
