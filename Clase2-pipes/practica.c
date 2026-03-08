/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practica.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 04:31:23 by rortiz            #+#    #+#             */
/*   Updated: 2026/03/09 02:13:45 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void child (int message_in, int message_out, int number)
{
	int		number_response;
	char	*message_received;

	message_received = recieved_number(message_in);
	if (message_received == (void*)0)
	{
		perror("No message recieved");
		exit(EXIT_FAILURE);
	}
	printf("Child received message: %s\n", message_received);
	if (atoi(message_received) > number)
		number_response = 2;
	else if (atoi(message_received) < number)
		number_response = 1;
	else
		number_response = 3;
	sending_number(message_out, number_response);
	printf("Child sent message: %d\n", number_response);
	if (number_response == 3)
		exit(EXIT_SUCCESS);
}

void fathers_guesser(int message_out, int message_in, int number)
{	
	char	*buffer_in;
	int		response;
	int		max;
	int		min;

	response = 4;
	max = 255;
	min = 0;
	while (response != 3)
	{
		sending_number(message_out, number);
		printf("Father sending message: %d\n", number);
		buffer_in = recieved_number(message_in);
		if (buffer_in == (void*)0)
		{
			perror("Father could not read message");
			exit(EXIT_FAILURE);
		}
		printf("Father recieved message: %s\n", buffer_in);
		response = atoi(buffer_in);
		if (response == 1)
			min = number;
		if (response == 2)
			max = number;
		number = generate_random_number(max, min);
		free(buffer_in);
	}
	printf("Father guessed number!!\n");
}


int main(int arg, char **argv)
{
	int		fd_PH[2];
	int		fd_HP[2];
	pid_t	child_pid;
	int		child_status;

	if (arg != 2)
	{
		printf("Please put only one argument, a number between 0 and 255\n");
		exit(EXIT_FAILURE);
	}
	
	if (pipe(fd_HP) == -1)
	{
		perror("Error while creating pipe from Child to Parent\n");
		exit(EXIT_FAILURE);
	}
	if (pipe(fd_PH) == -1)
	{
		perror("Error while creating pipe from Parent to Child\n");
		exit(EXIT_FAILURE);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Child could not be created");
		exit(EXIT_FAILURE);
	}
	switch (child_pid)
	{
		case 0:
			files_closer(fd_PH[1], "child\n");
			files_closer(fd_HP[0], "child\n");
			while (1)
				child(fd_PH[0], fd_HP[1], atoi(argv[1]));
			break;
		default:
			srand(time(NULL));
			int *first_number = (int *) malloc(sizeof(int));
			*first_number  = generate_random_number(255, 0);
			printf("The first number to be sent is: %d\n", *first_number);
			files_closer(fd_PH[0], "parent\n");
			files_closer(fd_HP[1], "parent\n");
			fathers_guesser(fd_PH[1], fd_HP[0], *first_number);
			waitpid(child_pid, &child_status,0);
			free(first_number);
			exit(EXIT_SUCCESS);
			break;
	}
}





