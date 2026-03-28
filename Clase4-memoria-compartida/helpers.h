/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:40:28 by rortiz            #+#    #+#             */
/*   Updated: 2026/03/28 09:49:27 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ipc.h>
#include <sys/shm.h>
#ifndef HELPERS_H
# define HELPERS_H

#define CLAVE_MESSSAGE	((key_t) 1001)
#define GUESSER 0
#define	OTHER	1
void	first_program(void);
void	second_program(void);
int	memory_creator_finder(key_t key, size_t memory_size);
void sending_message(int memory_id, unsigned char number, unsigned char my_turn, unsigned char other_turn);
int	receiving_message(int memory_id, unsigned char my_turn);
int	close_shared_memory(int memory_id);
int	generate_random_number(int max_number, int min_number);

typedef struct data DATA;
struct data 
{
	int		unEntero;
	float 	unFloat;
	char	unArray[10];
};
typedef	struct numbers_message NUMBER_MESSAGE;
struct numbers_message
{
	unsigned char	turn;
	unsigned char	number;
};
#endif