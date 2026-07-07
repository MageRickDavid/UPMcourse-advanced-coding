/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   programa2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 22:07:09 by rortiz            #+#    #+#             */
/*   Updated: 2026/07/07 01:38:00 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int				una_variable_global = -1;
int				t2_iterations = 0;
pthread_mutex_t	mut;
pthread_cond_t	cond;

void	*function1(void *arg)
{
	int			i;
	pthread_t	my_id;

	(void)arg;
    i = 0;
	my_id = pthread_self();
	printf("\n Hello, soy el thread 1 y me voy a dormir...\n");
	pthread_mutex_lock(&mut);
	while (t2_iterations < 3)
		pthread_cond_wait(&cond, &mut);
	pthread_mutex_unlock(&mut);

	while (i < 5)
	{
		una_variable_global = i;
		printf("\nHello, soy el thread 1 (%lu) y v.g. vale %d\n",
			(unsigned long)my_id, una_variable_global);
		sleep(1);
		i++;
	}
	printf("\nT1 says: bye bye!\n");
	return (NULL);
}

void	*function2(void *arg)
{
	pthread_t	my_id;
	int			i;
	float		*la_x;

	my_id = pthread_self();
	la_x = (float *)arg;
	i = 0;
	while (i < 8)
	{
		una_variable_global -= 3;
		printf("\nHello, soy el thread 2 (%lu) y v.g. vale %d\n",
			(unsigned long)my_id, una_variable_global);
		sleep(1);

		pthread_mutex_lock(&mut);
		t2_iterations++;
		if (t2_iterations == 3)
			pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mut);

		i++;
	}
	*la_x = 0.456;
	printf("\nT2 says: Hasta luego lucas!\n");
	return (NULL);
}

int main(void)
{
    pthread_t t1_id, t2_id;
    int i, err;
    float x;

    pthread_mutex_init(&mut, NULL);
    pthread_cond_init(&cond, NULL);
    x = 0.123;
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
    for (i = 0; i < 15; i++)
    {
        printf("\n Hello, soy el proceso principal: x vale %4.3f y la var. global vale %d\n", x, una_variable_global);
        sleep(1);
    }
    pthread_join(t1_id, NULL);
    pthread_join(t2_id, NULL);
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mut);
    return (0);
}