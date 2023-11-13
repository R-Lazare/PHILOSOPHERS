/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:39:31 by rluiz             #+#    #+#             */
/*   Updated: 2023/11/10 23:06:26 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putnbr(int nb, int i)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (nb < 0)
	{
		write(1, "-", 1);
		i++;
		nb = -nb;
	}
	if (nb > 9)
		i = i + ft_putnbr(nb / 10, i);
	i = i + ft_putchar(nb % 10 + '0');
	return (i);
}

int	ft_putnbr_base(unsigned int nb, char *base, unsigned int size, int i)
{
	if (nb >= size)
		i = i + ft_putnbr_base(nb / size, base, size, i);
	i = i + ft_putchar(base[nb % size]);
	return (i);
}

int	ft_pourcent(const char *src, va_list list, int i)
{
	int	nb;

	nb = 0;
	if (src[i] == 's')
		nb = nb + ft_putstr(va_arg(list, char *));
	else if (src[i] == 'd')
		nb = nb + ft_putnbr(va_arg(list, int), 0);
	return (nb);
}

int	ft_printf(t_table *table, const char *src, ...)
{
	int		i;
	int		nb;
	va_list	list;

	i = -1;
	nb = 0;
	va_start(list, src);
	pthread_mutex_lock(table->print);
	pthread_mutex_lock(table->dead_mutex);
	if (table->philos_dead)
	{
		pthread_mutex_unlock(table->dead_mutex);
		return (pthread_mutex_unlock(table->print));
	}
	while (src[++i])
	{
		if (src[i] == '%')
			nb = nb + ft_pourcent(src, list, ++i);
		else
			nb = nb + ft_putchar(src[i]);
	}
	va_end(list);
	pthread_mutex_unlock(table->dead_mutex);
	pthread_mutex_unlock(table->print);
	return (nb);
}
