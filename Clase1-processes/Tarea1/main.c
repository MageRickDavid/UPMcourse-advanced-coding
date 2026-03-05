/**
 * @file main.c
 * @author Ricardo
 * @date 2026-03-06
 * @brief tarea1
 */

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