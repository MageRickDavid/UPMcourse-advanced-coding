/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 07:21:58 by rortiz            #+#    #+#             */
/*   Updated: 2026/03/14 10:08:17 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#define Clave_msg1 1
#define	msg_type_PC 1
#define	msg_type_CP 2

void child (int msg_id, int number)
{
	char	received_number[101];
	char	number_to_send[5];
	int		len;
	int		number_response;
	int		sending_flag;

	len = receiving_message(msg_id, msg_type_PC, received_number);
	if (len < 0)
	{
		perror("Child did not receive a message");
		exit(EXIT_FAILURE);
	}
	printf("Child received the number: %s\n", received_number);
	if (atoi(received_number) > number)
		number_response = 2;
	else if (atoi(received_number) < number)
		number_response = 1;
	else
		number_response = 3;
	sprintf(number_to_send, "%d", number_response);
	sending_flag = sending_message(msg_id, number_to_send, msg_type_CP);
	if (sending_flag < 0)
	{
		perror("Child did not send a message");
		exit(EXIT_FAILURE);
	}
	printf("Child sent number: %s\n", number_to_send);
	if (number_response == 3)
		exit(EXIT_SUCCESS);
}

void fathers_guesser(int msg_id, int number)
{	
	char	received_number[101];
	char	number_to_send[5];
	int		len;
	int		response;
	int		sending_flag;
	int		max;
	int		min;

	response = 4;
	max = 255;
	min = 0;
	while (response != 3)
	{
		sprintf(number_to_send, "%d", number);
		sending_flag = sending_message(msg_id, number_to_send, msg_type_PC);
		if (sending_flag < 0)
		{
			perror("Parent did not send a message");
			exit(EXIT_FAILURE);
		}
		printf("Parent sent number: %s\n", number_to_send);
		len = receiving_message(msg_id, msg_type_CP, received_number);
		if (len < 0)
		{
			perror("Parent did not receive a message");
			exit(EXIT_FAILURE);
		}
		printf("Parent received the number: %s\n", received_number);
		response = atoi(received_number);
		if (response == 1)
			min = number;
		if (response == 2)
			max = number;
		number = generate_random_number(max, min);
	}
	printf("Father guessed number!!\n");
}

int	main(int arg, char **argv)
{
	pid_t	child_pid;
	int		msg_id;
	int		number_to_guess;
	int		child_status;
	
	if (arg != 2)
	{
		perror("Please input only one agument");
		exit(EXIT_FAILURE);
	}
	number_to_guess = atoi(argv[1]);
	msg_id = msgget(Clave_msg1, IPC_CREAT | 0666);
	child_pid = fork();
	if (child_pid < 0)
	{
		perror("Child could not be created");
		exit(EXIT_FAILURE);
	}
	switch (child_pid)
	{
		case 0:
			while(1)
				child(msg_id, number_to_guess);
			break;
		default:
			srand(time(NULL));
			int *first_number = (int *) malloc(sizeof(int));
			*first_number  = generate_random_number(255, 0);
			printf("The first number to be sent is: %d\n", *first_number);
			fathers_guesser(msg_id, *first_number);
			waitpid(child_pid, &child_status,0);
			exit(EXIT_SUCCESS);
			break;
	}
}