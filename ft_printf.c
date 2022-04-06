/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjlem <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:56:33 by mjlem             #+#    #+#             */
/*   Updated: 2021/12/14 20:10:54 by mjlem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minitalk.h"

int	ft_putchar(int c)
{
	write (1, &c, 1);
	return (1);
}

int	ft_putnbr(int nb)
{
	long	n ;
	int		l;

	l = 0;
	n = nb;
	if (n < 0)
	{
		l += ft_putchar('-');
		n = -n;
	}
	if (n < 10)
	{
		l += ft_putchar(n + '0');
	}
	else
	{
		l += ft_putnbr(n / 10);
		l += ft_putnbr(n % 10);
	}
	return (l);
}

int	convert(const char c, va_list arg)
{
	int	count;

	count = 0;
	if (c == 'd' )
		count += ft_putnbr(va_arg(arg, int));
	return (count);
}

int	ft_printf(const char *s, ...)
{
	va_list	arg;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(arg, s);
	while (s[i])
	{
		if (s[i] == '%' )
		{
			i++;
			count += convert(s[i++], arg);
		}
		else
			count += ft_putchar(s[i++]);
	}
	va_end(arg);
	return (count);
}
