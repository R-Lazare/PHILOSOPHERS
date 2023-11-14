/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:58:04 by rluiz             #+#    #+#             */
/*   Updated: 2023/11/14 17:10:04 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(char *error, pthread_mutex_t *print, t_arena *arena)
{
	pthread_mutex_lock(print);
	ft_putstr_fd(error, 1);
	if (arena)
		arena_destroy(arena);
	exit(EXIT_FAILURE);
}

int	get_time_ms(t_table *table)
{
	struct timeval	time;
	int				timems;

	gettimeofday(&time, NULL);
	if (table->time_start == 0)
		table->time_start = (int)(1000 * time.tv_sec) + (int)(time.tv_usec
				/ 1000);
	timems = (int)(1000 * time.tv_sec) + (int)(time.tv_usec / 1000)
		- table->time_start;
	return (timems);
}
