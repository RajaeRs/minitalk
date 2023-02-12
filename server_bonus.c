/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:51:52 by rrasezin          #+#    #+#             */
/*   Updated: 2023/02/12 22:39:35 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_value[4];

static int	check_value(int value)
{
	if (value < 192)
		return (1);
	if (value >= 192 && value < 224)
		return (2);
	if (value >= 224 && value < 240)
		return (3);
	else
		return (4);
}

static void	print_message(int *size, int *value, int *j, pid_t pid)
{
	int	i;

	i = 3;
	(*size)--;
	g_value[*size] = *value;
	if (*size == 0 && *value != 0)
	{
		while (i >= 0)
			write(1, &g_value[i--], 1);
		ft_bzero(g_value, sizeof(int) * 4);
	}
	if (*value == 0)
		kill(pid, SIGUSR2);
	*j = 8;
	*value = 0;
	return ;
}

static void	handler(int signum, siginfo_t *info, void *context)
{
	static pid_t	pid;
	static int		value;
	static int		j;
	static int		size;

	(void) context;
	if (pid != info->si_pid)
	{
		pid = info->si_pid;
		j = 8;
		value = 0;
		size = 0;
		ft_bzero(g_value, sizeof(int) * 4);
	}
	if (signum == SIGUSR1)
		value += ft_pow(2, j);
	j--;
	if (j == 4 && size == 0)
		size = check_value(value);
	if (j == -1)
		print_message(&size, &value, &j, info->si_pid);
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
