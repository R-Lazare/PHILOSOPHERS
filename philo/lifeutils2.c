/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifeutils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:41:36 by rluiz             #+#    #+#             */
/*   Updated: 2023/11/24 11:58:12 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_ftaken(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork->fork_taken);
	pthread_mutex_lock(philo->left_fork->fork_taken);
}

void	unlock_ftaken(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork->fork_taken);
	pthread_mutex_unlock(philo->right_fork->fork_taken);
}

void	check(t_philo *philo)
{
	pthread_mutex_unlock(philo->table->death_mutex);
	if (philo->id % 2 == 0)
	{
		lock_ftaken(philo);
		if (philo->right_fork->is_taken == philo->id)
			pthread_mutex_unlock(philo->right_fork->fork);
		if (philo->left_fork->is_taken == philo->id)
			pthread_mutex_unlock(philo->left_fork->fork);
		unlock_ftaken(philo);
	}
	else
	{
		lock_ftaken(philo);
		if (philo->left_fork->is_taken == philo->id)
			pthread_mutex_unlock(philo->left_fork->fork);
		if (philo->right_fork->is_taken == philo->id)
			pthread_mutex_unlock(philo->right_fork->fork);
		unlock_ftaken(philo);
	}
}

void	check_and_exec(void (*func)(t_philo *), t_philo *philo)
{
	pthread_mutex_lock(philo->table->death_mutex);
	if (philo->table->philo_dead || philo->table->philos_full)
	{
		check(philo);
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(philo->table->death_mutex);
	func(philo);
}

void	one_philo(t_table *table)
{
	ft_printf(table, "%d %d has taken a fork\n", get_time_ms(table),
		table->philos[0].id);
	usleep(table->time_to_die * 1000);
	ft_printf(table, "%d %d died\n", get_time_ms(table), table->philos[0].id);
	pthread_mutex_lock(table->death_mutex);
	table->philo_dead = 1;
	pthread_mutex_unlock(table->death_mutex);
	arena_destroy(table->arena);
	exit(0);
}
