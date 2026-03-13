/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 02:11:10 by rortiz            #+#    #+#             */
/*   Updated: 2026/03/14 07:13:23 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#define Clave_msg1 1
#define	msg_type 3


void child(void)
{
	int		msg_id;
	int		len;
	int		close_flag;
	char	message[MAX_LENGTH];
	
	msg_id = message_creator_finder(Clave_msg1);
	if (msg_id < 0)
	{
		perror("Child could not find message_queue");
		exit(EXIT_FAILURE);
	}
	len = receiving_message(msg_id, msg_type, message);
	if (len < 0)
	{
		perror("Child could not receive message");
		exit(EXIT_FAILURE);
	}
	printf("Child received the next message: %s\n", message);
	close_flag = close_queue(msg_id);
	if (close_flag < 0)
	{
		perror("message_queue could not be closed");
		exit(EXIT_FAILURE);
	}
}

void fathers_messenger(char *message)
{
	int		msg_id;
	int		sending_flag;
	
	msg_id = message_creator_finder(Clave_msg1);
	if (msg_id < 0)
	{
		perror("Father could not find message_queue");
		exit(EXIT_FAILURE);
	}
	sending_flag = sending_message(msg_id, message, msg_type);
	if (sending_flag < 0)
	{
		perror("Father could not send message");
		exit(EXIT_FAILURE);
	}
	printf("The Father sent this message: %s\n", message);
}

int	main(int arg, char **argv)
{
	pid_t	pid_child;
	int		status;

	if (arg != 2)
	{
		printf("Please write down a message");
		exit(EXIT_FAILURE);
	}
	pid_child = fork();
	if (pid_child < 0)
	{
		perror("Error while creating child");
		exit(EXIT_FAILURE);
	}
	if (pid_child == 0)
	{
		child();
		exit(EXIT_SUCCESS);
	}
	fathers_messenger(argv[1]);
	waitpid(pid_child, &status, 0);
	printf("All processes finished\n");
	exit(EXIT_FAILURE);
}



