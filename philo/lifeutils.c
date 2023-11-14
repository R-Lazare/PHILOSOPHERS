/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifeutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:00:41 by rluiz             #+#    #+#             */
/*   Updated: 2023/11/14 01:52:41 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_and_exec(int (*func)(t_philo), t_table *table, int id)
{
	pthread_mutex_lock(table->death_mutex);
	if (table->philo_dead)
	{
		pthread_mutex_unlock(table->death_mutex);
		return ;
	}
	func(table->philos[id]);
}