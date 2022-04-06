/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 05:50:22 by mjlem             #+#    #+#             */
/*   Updated: 2022/02/19 10:53:44 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

char	g_byte[8];

int	ft_power(int nb, int power)
{
	int	n;

	n = nb;
	if (power == 0)
		return (1);
	if (power < 0)
		return (0);
	while (power > 1)
	{
		n = n * nb;
		power--;
	}
	return (n);
}

void	convert_byte(int i, siginfo_t *info)
{
	int	p;
	int	c;

	p = 0;
	c = 0;
	while (i >= 0)
	{
		--i;
		if (g_byte[i] == '1')
			c += ft_power(2, p);
		p++;
	}
	if (c == 0)
		kill(info->si_pid, SIGUSR2);
	write(1, &c, 1);
}

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static int	i = 0;
	static int	last_pid = 0;

	context = NULL;
	if ((info->si_pid != last_pid) && i)
	{
		while (i <= 0)
		g_byte[i--] = '0';
		i = 0;
	}
	if (signum == SIGUSR1)
		g_byte[i++] = '1';
	else if (signum == SIGUSR2)
		g_byte[i++] = '0';
	if (i == 8)
	{
		convert_byte(i, info);
		i = 0;
	}
	last_pid = info->si_pid;
}

int	main(void)
{
	int					pid;
	struct sigaction	act;

	pid = getpid();
	ft_printf("PID: %d\n", pid);
	act.sa_sigaction = &sig_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
}
