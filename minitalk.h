/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:58:15 by rrasezin          #+#    #+#             */
/*   Updated: 2023/02/12 22:36:05 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>

pid_t	mini_atoi(char *src);
int		check_errors(int ac, char **av, pid_t *pid);
int		ft_pow(int base, int power);
void	ft_bzero(void *src, size_t len);
void	ft_putnbr(int n);

#endif