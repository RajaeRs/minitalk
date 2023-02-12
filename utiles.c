/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:01:25 by rrasezin          #+#    #+#             */
/*   Updated: 2023/02/12 15:57:31 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

pid_t	mini_atoi(char *src)
{
	pid_t	pid;
	int		i;

	pid = 0;
	i = 0;
	if (src[i] == '\0' || src == NULL)
		return (-1);
	if (src[i] && (src[i] < '0' || src[i] > '9'))
		return (-2);
	while (src[i])
	{
		if (src[i] < '0' || src[i] > '9')
			break ;
		pid = pid * 10 + src[i] - '0';
		i++;
	}
	if (src[i])
		return (-2);
	return (pid);
}

int	check_errors(int ac, char **av, pid_t *pid)
{
	write (2, "\033[1m\033[33:5:5m", 14);
	if (ac != 3)
	{
		write (2, "\n  [!]  Tap the pid and one message to send -_- .\n\n", 51);
		return (1);
	}
	(*pid) = mini_atoi(av[1]);
	if (av[1][0] == '\0' || av[2][0] == '\0' || *pid == -1)
	{
		write (2, "\n  [!]  The pid or the message is empty -_- .\n\n", 47);
		return (1);
	}
	if (*pid == -2)
	{
		write (2, "\n  [!]  The pid must be a number and positive", 45);
		write (2, ", no space no signe.\n\n", 22);
		return (1);
	}
	if (*pid == 1 || *pid == 0)
	{
		write (2, "\n  \033[1m\033[31:5:5m[x]  Illegal pid !!!.\n\n", 39);
		return (1);
	}
	return (0);
}

int	ft_pow(int	base, int power)
{
	int	result;

	result = 1;
	while (power--)
	{
		result = result * base;
	}
	return (result);
}

void	ft_bzero(void *src, size_t len)
{
	unsigned char	*dest;

	dest = (unsigned char *)src;
	while (len)
	{
		*dest = 0;
		dest++;
		len--;
	}
}

void	ft_putnbr(int n)
{
	char	val;

	val = 0;
	if (n == -2147483648)
	{
		write (1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write (1, "-", 1);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		val = n + 48;
		write (1, &val , 1);
	}
}
