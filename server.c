/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:48:06 by rrasezin          #+#    #+#             */
/*   Updated: 2023/02/12 22:41:07 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handler(int signum, siginfo_t *info, void *context)
{
	static pid_t	pid;
	static int		value;
	static int		j;

	(void) context;
	if (pid != info->si_pid)
	{
		pid = info->si_pid;
		j = 0;
		value = 0;
	}
	if (signum == SIGUSR1)
		value += ft_pow(2, j);
	j++;
	if (j == 7)
	{
		write (1, &value, 1);
		j = 0;
		value = 0;
	}
}

int	main(void)
{
	pid_t				s_pid;
	struct sigaction	sa;
	int					error;

	s_pid = getpid();
	ft_putnbr(s_pid);
	write (1, "\n", 1);
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	error = sigaction(SIGUSR1, &sa, NULL);
	error = sigaction(SIGUSR2, &sa, NULL);
	if (error != 0)
		return (1);
	while (1)
		;
}
