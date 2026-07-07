/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practica.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 22:02:32 by rortiz            #+#    #+#             */
/*   Updated: 2026/07/07 02:18:43 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t  mut;
pthread_cond_t   cond1, cond2;

/* *************** INICIO CORRECCION *************** */

# define THREAD_1 1
# define THREAD_2 2

int turno = THREAD_1;

/* **************** FIN CORRECCION **************** */

void    pausa()
{
  int pausa;
 
  pausa = 500+(int)(1000*(random()/(float)RAND_MAX));
  usleep(pausa*1000);
}

void*   function1(void *arg)
{
    int i;
     
    i = 0;
    pthread_t my_id = pthread_self();

    (void)arg;

    for (i = 0; i < 10; i++)
    {
        /* *************** INICIO CORRECCION *************** */

        pthread_mutex_lock(&mut);

        while (turno != THREAD_1)
        {
            printf("\n Thread 1 wait...\n");
            pthread_cond_wait(&cond1, &mut);
        }

        printf("\n Thread 1 fine wait...\n");

        /* **************** FIN CORRECCION **************** */

        printf("\n Soy el thread 1 (%lu) DENTRO en mi seccion critica...\n",
            (unsigned long)my_id);

        pausa();

        /* *************** INICIO CORRECCION *************** */

        turno = THREAD_2;

        printf("\n Thread 1 signal...\n");
        pthread_cond_signal(&cond2);

        pthread_mutex_unlock(&mut);

        /* **************** FIN CORRECCION **************** */

        printf("\n Soy el thread 1 (%lu) FUERA en mi seccion critica...\n",
            (unsigned long)my_id);

        pausa();
    }
    return NULL;
}
 
void*   function2(void *arg)
{
    pthread_t my_id = pthread_self();
    int i;

    (void)arg;

    /*
    ** Ya no hace falta mandar una signal inicial.
    ** La variable turno indica que empieza thread 1.
    */

    for (i = 0; i < 10; i++)
    {
        /* *************** INICIO CORRECCION *************** */

        pthread_mutex_lock(&mut);

        while (turno != THREAD_2)
        {
            printf("\n Thread 2 wait...\n");
            pthread_cond_wait(&cond2, &mut);
        }

        printf("\n Thread 2 fine wait...\n");

        /* **************** FIN CORRECCION **************** */

        printf("\n Soy el thread 2 (%lu) DENTRO en mi seccion critica...\n",
            (unsigned long)my_id);

        pausa();

        /* *************** INICIO CORRECCION *************** */

        turno = THREAD_1;

        printf("\n Thread 2 signal...\n");
        pthread_cond_signal(&cond1);

        pthread_mutex_unlock(&mut);

        /* **************** FIN CORRECCION **************** */

        printf("\n Soy el thread 2 (%lu) FUERA en mi seccion critica...\n",
            (unsigned long)my_id);

        pausa();
    } 
    return NULL;
}
 
int main(void)
{
  pthread_t t1_id, t2_id;
  int   err;
  float x = 0.123;

  pthread_mutex_init(&mut,NULL);
  pthread_cond_init(&cond1,NULL);
  pthread_cond_init(&cond2,NULL);

  err = pthread_create(&t1_id, NULL, &function1, NULL);
  if (err != 0)
    printf("\ncan't create thread :[%s]", strerror(err));
  else
    printf("\n Thread created successfully\n");

  err = pthread_create(&t2_id, NULL, &function2, &x);
  if (err != 0)
    printf("\ncan't create thread :[%s]", strerror(err));
  else
    printf("\n Thread created successfully\n");

  printf("\n Soy el proceso principal, espero a que los threads terminen...\n");

  pthread_join(t1_id, NULL);
  printf("\n T1 ha terminado\n");

  pthread_join(t2_id, NULL);
  printf("\n T2 ha terminado\n");

  pthread_cond_destroy(&cond1);
  pthread_cond_destroy(&cond2);
  pthread_mutex_destroy(&mut);

  return 0;
}