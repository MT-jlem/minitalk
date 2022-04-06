/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:32:33 by mjlem             #+#    #+#             */
/*   Updated: 2022/02/17 18:31:54 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minitalk.h"

void	ft_send(char c, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((128 >> i) & c)
			kill (pid, SIGUSR1);
		else
			kill (pid, SIGUSR2);
		usleep(500);
		i++;
	}
}

void	handler(int signum)
{
	if (signum == SIGUSR2)
		write(1, "--Message-received--\n", 21);
	exit(0);
}

int	main(int ac, char **av)
{
	int	i;
	int	pid;
	int	l;

	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		i = 0;
		l = ft_strlen(av[2]);
		if (pid <= 0)
			exit(1);
		signal(SIGUSR2, handler);
		while (i <= l)
		{
			ft_send(av[2][i], pid);
			i++;
		}
	}
	return (0);
}
