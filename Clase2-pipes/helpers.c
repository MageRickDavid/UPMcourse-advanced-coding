/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 16:23:08 by rortiz            #+#    #+#             */
/*   Updated: 2026/03/09 02:34:16 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

/**
 * @brief This function outputs the length of a string
 * @param {char*} str: The string to get the length from
 * @return {int} The length of the string
 */
int	ft_strlen(char *str)
{
	int		i;
	
	i = 0;
	while (str[i])
		i++;
	return (i);
}

/**
 * @brief The file descriptor to which receive the message from
 * @param {int} fd: File descriptor
 * @return {char*} The message received.
 */
char	*recieved_number(int fd)
{
	char	*buffer;
	int		bytes_read;
	
	buffer = (char *) malloc(sizeof(char) * 101);
	if (buffer == (void*)0)
	{
		perror("Error malloc");
		exit(EXIT_FAILURE);
	}
	bytes_read = read(fd, buffer, 100);
	if (bytes_read == -1)
	{
		perror("Error reading message");
		return ((void*)0);
	}
	buffer[bytes_read] = '\0';
	return (buffer);
}

/**
 * @brief This function sends a number through a file descriptor (like a piping)
 * @param {int} fd: The file descriptor.
 * @param {int} number: The number to send.
 * @return {void}
 */
void	sending_number(int fd, int number)
{
	char	buffer[101];
	int		len;
	int		bytes_written;
	
	sprintf(buffer, "%d", number);
	len = ft_strlen(buffer);
	bytes_written = write(fd, buffer, len);
	if (bytes_written == -1)
	{
		perror("Error sending number");
		exit(EXIT_FAILURE);
	}
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

/**
 * @brief This function closes a file descriptor
 * @param {int} fd: The file descriptor to close.
 * @param {char*} name: The name of the process closing the file descriptor
 * @return {void}
 */
void	files_closer(int fd, char *name)
{
	char	error_message[101];
	
	sprintf(error_message, "%s could not close the file descriptor", name);
	if (close(fd) == -1)
	{
		perror(error_message);
		exit(EXIT_FAILURE);
	}
}