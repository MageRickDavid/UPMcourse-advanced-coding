/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 07:46:53 by rortiz            #+#    #+#             */
/*   Updated: 2026/03/06 09:46:33 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


void change_number(int *z, int new_number)
{
    *z = new_number;
    printf("I am a child process, my id is: %d and my parent is %d\n", (int) getpid(), (int) getppid());
    printf("The new value is: %d and the address is: %p\n", *z, z);
}

int main(void)
{
    int     z;
    int     status;
    pid_t   pid_number1;
    pid_t   pid_number2;
    
    
    z = 10;
    pid_number1 = fork();
    if (pid_number1 == 0)
    {
        printf("First child created!\n");
        change_number(&z, 20);
        exit(EXIT_SUCCESS);   
    } 
    else if (pid_number1 < 0)
    {
        perror("Creating first child failed\n");
        exit(EXIT_FAILURE);
    }
    pid_number2 = fork();
    if (pid_number2 == 0)
    {
        printf("Second child created!\n");
        change_number(&z, 30);
        exit(EXIT_SUCCESS);   
    } 
    else if (pid_number2 < 0)
    {
        perror("Creating second child failed\n");
        exit(EXIT_FAILURE);
    }
    printf("The value of z is: %d and its address is: %p\n", z, &z);
    printf("I am a parent process, my id is: %d\n", (int) getpid());
    waitpid(pid_number1, &status, 0);
    printf("First child finished!\n");
    waitpid(pid_number2, &status, 0);
    printf("Second child finished!\n");   
}