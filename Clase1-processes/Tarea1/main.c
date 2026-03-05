/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 03:58:48 by rortiz            #+#    #+#             */
/*   Updated: 2026/03/06 03:58:51 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "fun.h"
 #include <unistd.h>
 #include <stdio.h>

 void ft_putstr(char *str)
 {
	char	*copy;

	copy = str;
	while (*copy)
	{
		write(1, copy, 1);
		copy++;
	}
 }

 int	main(void)
 {
	int	input_integer;
	ft_putstr("Please input a number: ");
	scanf("%d", &input_integer);
	printf("The result is: %f \n", div(input_integer));
	return (0);
 }