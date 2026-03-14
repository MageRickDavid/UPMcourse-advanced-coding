/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 02:28:34 by rortiz            #+#    #+#             */
/*   Updated: 2026/03/14 07:21:31 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#ifndef HELPERS_H
# define HELPERS_H
#define MAX_LENGTH 60

int     message_creator_finder(key_t key);
int     sending_message(int msg_id, char *str, long type);
int     receiving_message(int msg_id, long type, char buffer[MAX_LENGTH]);
int     close_queue(int msg_id);
int     generate_random_number(int max_number, int min_number);
typedef struct msgbuf {
		long mtype;
		char mtext[MAX_LENGTH];
	} message_queue;

#endif