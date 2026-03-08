/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rortiz <rortiz@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 04:04:39 by rortiz            #+#    #+#             */
/*   Updated: 2026/03/09 02:17:30 by rortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

/**
 * @brief This function is used to get information from the system,
 * We aim to display the pid and the group it belongs to
 * @param {void}
 * @return {void}
 */
void	get_info(void)
{
	uid_t			my_id;
	struct passwd	*my_passwd;
	struct group	*my_group;
	pid_t			my_process;
	pid_t			my_parent_process;
	char			**miembros;
	
	my_process = getpid();
	my_parent_process = getppid();
	printf("EL ID del proceso es %d y el de su padre es %d \n", my_process, my_parent_process);
	my_id = getuid();
	my_passwd = getpwuid(my_id);
	if (my_passwd == (void*)0)
	{
		printf("There was no user %d \n", (int) my_process);
		exit(EXIT_FAILURE);
		
	}
	printf("Soy: %s \n", my_passwd->pw_gecos);
	printf("Mi login es: %s \n", my_passwd->pw_name);
	printf("Mi id es: %d \n", (int) (my_passwd->pw_uid));
	printf("Mi directorio de trabajo es: %s\n", my_passwd->pw_dir);
	printf("Mi shell es: %s\n", my_passwd->pw_shell);
	my_group = getgrgid(my_passwd->pw_gid);
	if (my_group == (void*)0)
	{
		printf("No encuentro el grupo %d \n", (int)(my_passwd->pw_gid));
		exit(EXIT_FAILURE);
	}
	printf("Los miembros del grupo son: \n");
	miembros = my_group->gr_mem;
	while (*miembros)
	{
		printf("%s\n", *miembros);
		miembros++;
	}
	exit(EXIT_SUCCESS);
}

int	main(void)
{
	get_info();
	return (0);
}