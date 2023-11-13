/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:36:47 by rluiz             #+#    #+#             */
/*   Updated: 2023/11/09 18:43:30 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *src)
{
	int	i;

	i = 0;
	if (!src)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (src[i])
	{
		write(1, &src[i], 1);
		i++;
	}
	return (i);
}
