/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   programa2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 00:32:35 by rortiz            #+#    #+#             */
/*   Updated: 2026/07/06 01:28:53 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"

int main(void)
{
    int     i;
    int     semid;
    struct  sembuf  operacion;
    
    srandom(getpid());
    semid = semget(CLAVE, 1, IPC_CREAT | 0600);
    if (semid == -1)
    {
        perror("semget");
        exit(EXIT_FAILURE);
    }
    printf("Semaphore value: %d\n", semctl(semid, SEM_1, GETVAL));
    operacion.sem_flg = 0;
    i = 10;
    while (i > 0)
    {
        i--;
        printf("B: espero sem1\n");
        operacion.sem_num = SEM_1;
        operacion.sem_op = -1;
        semop(semid, &operacion, 1);
        pausa();
        printf("B: libero sem1\n");
        operacion.sem_num = SEM_1;
        operacion.sem_op = 1;
        semop(semid, &operacion, 1);
        printf("Process B out! (%d)\n", i);
        pausa();
    }
    semctl(semid, 0, IPC_RMID);
    printf("Fin! \n");
    return (0);
}