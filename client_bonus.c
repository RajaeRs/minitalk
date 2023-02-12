/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:22:25 by rrasezin          #+#    #+#             */
/*   Updated: 2023/02/12 22:37:30 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	send_message(char *message, pid_t pid)
{
	int		i;
	int		j;
	int		error;

	i = -1;
	error = 0;
	while (message[++i] || message[i] == '\0')
	{
		j = 9;
		while (--j >= 0)
		{
			if (((message[i] >> j) & 1) == 1)
				error = kill(pid, SIGUSR1);
			else
				error = kill(pid, SIGUSR2);
			if (error == -1)
				return (1);
			usleep(200);
		}
		if (message[i] == '\0')
			break ;
	}
	return (0);
}

static void	handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGUSR2)
	{
		write (1, "\n  \033[1m\033[32:5:5m[SUCCESSE]  message reseved.\n\n", 46);
		exit (0);
	}
}

int	main(int argc, char **argv)
{
	pid_t				s_pid;
	int					error;
	struct sigaction	sa;

	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR2, &sa, NULL);
	error = check_errors(argc, argv, &s_pid);
	if (error == 1)
		exit (1);
	if (send_message(argv[2], s_pid) == 1)
	{
		write (2, "\n  \033[1m\033[31:5:5m[x]  The message not sand,", 43);
		write (2, " check the pid.\n\n", 17);
		exit (1);
	}
	while (1)
		;
}
