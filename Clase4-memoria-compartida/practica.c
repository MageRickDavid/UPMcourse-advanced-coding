/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practica.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 08:21:28 by rortiz            #+#    #+#             */
/*   Updated: 2026/03/28 10:06:55 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>


void process1_guesser(key_t key, int max, int min)
{
    int             memory_id;
    int             number;
    
    memory_id = memory_creator_finder(key, sizeof(NUMBER_MESSAGE));
    if (memory_id < 0)
        exit(EXIT_FAILURE);
    while(1)
    {
        number = generate_random_number(max, min);
        sending_message(memory_id,(unsigned char)number, GUESSER, OTHER);
        while (receiving_message(memory_id, GUESSER) < 0){}
        if (receiving_message(memory_id, GUESSER) == 1)
            min = number;
        else if (receiving_message(memory_id, GUESSER) == 2)
            max = number;
        else if (receiving_message(memory_id, GUESSER) == 3)
        {
            printf("Guesser was told by other that it won!!!\n");
            return;
        }   
    }
}

void process2_other(key_t key, unsigned char number_to_guess)
{
    int             memory_id;
    
    memory_id = memory_creator_finder(key, sizeof(NUMBER_MESSAGE));
    if (memory_id < 0)
        exit(EXIT_FAILURE);
    while(1)
    {
        while (receiving_message(memory_id, OTHER) < 0){}
        if (receiving_message(memory_id, OTHER) < number_to_guess)
            sending_message(memory_id, 1, OTHER, GUESSER);
        else if (receiving_message(memory_id, OTHER) > number_to_guess)
            sending_message(memory_id, 2, OTHER, GUESSER);
        else if (receiving_message(memory_id, OTHER) == number_to_guess)
        {
            printf("OTHER ACKNOWLEDGES GUESSER WON");
            sending_message(memory_id, 3, OTHER, GUESSER);
            return ;
        }
    }
}

int main(int args, char **argv)
{
    pid_t         child;
    unsigned char number_to_guess;
    int           status;
    
    if (args != 2)
    {
        printf("Please input only one argument\n");
        exit(EXIT_FAILURE);
    }
    number_to_guess = atoi(argv[1]);
    child = fork();

    if (child == 0)
    {
        process2_other(CLAVE_MESSSAGE, number_to_guess);
        exit(EXIT_SUCCESS);
    }
    process1_guesser(CLAVE_MESSSAGE, 100, 0);
    waitpid(child, &status, 0);
    exit(EXIT_SUCCESS);
}