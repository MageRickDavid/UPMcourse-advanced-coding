/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practica.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 09:22:05 by rortiz            #+#    #+#             */
/*   Updated: 2026/07/07 12:58:30 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"
#include <stdio.h>

int	main(void)
{
	int	vector[] = {5, 2, 4, 3};
	int	num_elem;
	int	i;

	num_elem = sizeof(vector) / sizeof(vector[0]);
	printf("Before: ");
	i = 0;
	while (i < num_elem)
	{
		printf("%d ", vector[i]);
		i++;
	}
	printf("\n");
	sort(vector, num_elem);
	printf("After:  ");
	i = 0;
	while (i < num_elem)
	{
		printf("%d ", vector[i]);
		i++;
	}
	printf("\n");
	return (0);
}