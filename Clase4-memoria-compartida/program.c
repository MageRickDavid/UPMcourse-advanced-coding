/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:52:28 by rortiz            #+#    #+#             */
/*   Updated: 2026/03/28 06:23:05 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


/**
 * @brief Sends a message to a shared memory
 */
void	first_program(void)
{
	int		memory_id;
	DATA	*common_area;
	
	memory_id = shmget(CLAVE_MESSSAGE, sizeof(DATA), IPC_CREAT | 0666);
	if (memory_id == -1)
	{
		perror("shmget could not create a new common area");
		exit(EXIT_FAILURE);
	}
	common_area = (DATA*)shmat(memory_id, 0, 0);
	strcpy(common_area->unArray, "012345678");
	common_area->unEntero = 42;
	common_area->unFloat = 3.141516;
	printf("I just finished sending the message\n");
	exit(EXIT_SUCCESS);
}

/**
 * @brief Reads the message from the shared memory
 */
void	second_program(void)
{
	int		memory_id;
	int		destruction_flag;
	DATA	*common_area;
	
	memory_id = shmget(CLAVE_MESSSAGE, sizeof(DATA), IPC_CREAT | 0666);
	if (memory_id == -1)
	{
		perror("shmget could not create a new common area");
		exit(EXIT_FAILURE);
	}
	common_area = (DATA*)shmat(memory_id, 0, 0);
	printf("I am about the read the message\n");
	printf("The message received is: %s\n", common_area->unArray);
	printf("The integer received is: %d\n", common_area->unEntero);
	printf("The float received is: %f\n", common_area->unFloat);
	destruction_flag = shmctl(memory_id, IPC_RMID, 0);
	if (destruction_flag == -1)
	{
		perror("The memory segment could not be destroyed");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int	main(void)
{
	pid_t	child;
	int		status;
	
	child = fork();
	if (child == 0)
	{
		second_program();
		exit(EXIT_SUCCESS);
	}
	first_program();
	waitpid(child, &status, 0);
	exit(EXIT_SUCCESS);
}