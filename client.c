/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:13:14 by rrasezin          #+#    #+#             */
/*   Updated: 2023/02/12 22:38:19 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	send_message(char *message, pid_t pid)
{
	int		i;
	int		j;
	int		error;

	i = 0;
	error = 0;
	while (message[i])
	{
		j = 0;
		while (j < 7)
		{
			if (((message[i] >> j) & 1) == 1)
				error = kill(pid, SIGUSR1);
			else
				error = kill(pid, SIGUSR2);
			j++;
			if (error == -1)
				return (1);
			usleep(300);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t	s_pid;
	int		error;

	error = check_errors(argc, argv, &s_pid);
	if (error == 1)
		exit (1);
	if (send_message(argv[2], s_pid) == 1)
	{
		write (2, "\n  \033[1m\033[31:5:5m[x]  The message not sand,", 43);
		write (2, " check the pid.\n\n", 17);
		exit (1);
	}
}
