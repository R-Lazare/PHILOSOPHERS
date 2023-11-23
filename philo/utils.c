/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:58:04 by rluiz             #+#    #+#             */
/*   Updated: 2023/11/23 19:35:43 by rluiz            ###   ########.fr       */
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
	pthread_mutex_lock(table->time_mutex);
	if (table->time_start == 0)
		table->time_start = (int)(1000 * time.tv_sec) + (int)(time.tv_usec
			/ 1000);
	timems = (int)(1000 * time.tv_sec) + (int)(time.tv_usec / 1000)
		- table->time_start;
	pthread_mutex_unlock(table->time_mutex);
	return (timems);
}
void	lock_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork->fork_taken);
	if (!philo->left_fork->is_taken)
	{
		pthread_mutex_lock(philo->left_fork->fork);
		philo->left_fork->is_taken = philo->id;
		pthread_mutex_unlock(philo->left_fork->fork_taken);
		philo->two_forks += 1;
		ft_printf(philo->table, "%d ms %d has taken a fork\n",
			get_time_ms(philo->table), philo->id);
	}
	else
		pthread_mutex_unlock(philo->left_fork->fork_taken);
}

void	lock_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork->fork_taken);
	if (!philo->right_fork->is_taken)
	{
		philo->right_fork->is_taken = philo->id;
		pthread_mutex_unlock(philo->right_fork->fork_taken);
		pthread_mutex_lock(philo->right_fork->fork);
		philo->two_forks += 1;
		ft_printf(philo->table, "%d ms %d has taken a fork\n",
			get_time_ms(philo->table), philo->id);
	}
	else
		pthread_mutex_unlock(philo->right_fork->fork_taken);
}

int	near_philo_locked(t_philo *philo)
{
	t_philo	*philo_right;
	t_philo	*philo_left;

	philo_right = &philo->table->philos[philo->id % philo->table->num_of_philos];
	philo_left = &philo->table->philos[(philo->id - 2) + philo->table->num_of_philos * (philo->id == 1)];
	lock_ftaken(philo_right);
	if (philo_right->left_fork->is_taken == philo_right->id)
	{
		unlock_ftaken(philo_right);
		return (1);
	}
	unlock_ftaken(philo_right);
	lock_ftaken(philo_left);
	if (philo_left->right_fork->is_taken == philo_left->id)
	{
		unlock_ftaken(philo_left);
		return (1);
	}
	unlock_ftaken(philo_left);
	return (0);
}
