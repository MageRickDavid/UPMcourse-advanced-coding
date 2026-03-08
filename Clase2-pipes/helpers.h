/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 16:34:36 by rortiz            #+#    #+#             */
/*   Updated: 2026/03/08 19:08:15 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

int		ft_strlen(char *str);
int		generate_random_number(int max_number, int min_number);
void	sending_number(int fd, int number);
void	files_closer(int fd, char *name);
char	*recieved_number(int fd);

#endif