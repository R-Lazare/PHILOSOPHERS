/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifeutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:00:41 by rluiz             #+#    #+#             */
/*   Updated: 2023/11/22 19:15:18 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_and_exec(void (*func)(t_philo *), t_philo *philo)
{
	pthread_mutex_lock(philo->table->death_mutex);
	if (philo->table->philo_dead || philo->table->philos_full)
	{
		pthread_mutex_unlock(philo->table->death_mutex);
		if (philo->id % 2 == 1)
		{
			pthread_mutex_lock(philo->right_fork->fork_taken);
			if (philo->right_fork->is_taken != 0)
				pthread_mutex_unlock(philo->right_fork->fork);
			pthread_mutex_unlock(philo->right_fork->fork_taken);
			pthread_mutex_lock(philo->left_fork->fork_taken);
			if (philo->left_fork->is_taken != 0)
				pthread_mutex_unlock(philo->left_fork->fork);
			pthread_mutex_unlock(philo->left_fork->fork_taken);
		}
		else if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork->fork_taken);
			if (philo->left_fork->is_taken != 0)
				pthread_mutex_unlock(philo->left_fork->fork);
			pthread_mutex_unlock(philo->left_fork->fork_taken);
			pthread_mutex_lock(philo->right_fork->fork_taken);
			if (philo->right_fork->is_taken != 0)
				pthread_mutex_unlock(philo->right_fork->fork);
			pthread_mutex_unlock(philo->right_fork->fork_taken);
		}
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(philo->table->death_mutex);
	func(philo);
}

void	philo_eat(t_philo *philo)
{
	lock_ftaken(philo);
	if (philo->right_fork->is_taken == philo->id
		&& philo->left_fork->is_taken == philo->id)
	{
		unlock_ftaken(philo);
		philo->time_last_meal = get_time_ms(philo->table);
		ft_printf(philo->table, "%d ms %d is eating\n",
			get_time_ms(philo->table), philo->id);
		usleep(philo->table->time_to_eat * 1000);
		philo->meals++;
		check_exit(philo);
		lock_ftaken(philo);
		philo->right_fork->is_taken = 0;
		philo->left_fork->is_taken = 0;
		unlock_ftaken(philo);
	}
	unlock_ftaken(philo);
}

void	philo_lock1(t_philo *philo)
{
	if (!near_philo_locked(philo))
	{
		if (philo->id % 2 == 1)
			lock_left_fork(philo);
		else
			lock_right_fork(philo);
	}
}

void	philo_lock2(t_philo *philo)
{
	if (!near_philo_locked(philo))
	{
		if (philo->id % 2 == 1)
			lock_right_fork(philo);
		else
			lock_left_fork(philo);
	}
}

void	philo_sleep_think(t_philo *philo)
{
	ft_printf(philo->table, "%d ms %d is sleeping\n", get_time_ms(philo->table),
		philo->id);
	usleep(philo->table->time_to_sleep * 1000);
	ft_printf(philo->table, "%d ms %d is thinking\n", get_time_ms(philo->table),
		philo->id);
}

void	*philo_life(void *philo)
{
	t_philo	*philo2;

	philo2 = (t_philo *)philo;
	while (1)
	{
		// pthread_mutex_lock(philo2->table->table_mutex);
		check_and_exec(&philo_lock1, philo2);
		check_and_exec(&philo_lock2, philo2);
		// pthread_mutex_unlock(philo2->table->table_mutex);
		lock_ftaken(philo2);
		if (philo2->right_fork->is_taken == philo2->id
			&& philo2->left_fork->is_taken == philo2->id)
		{
			unlock_ftaken(philo2);
			check_and_exec(&philo_eat, philo2);
			check_and_exec(&philo_sleep_think, philo2);
		}
		else
			unlock_ftaken(philo2);
	}
	return (NULL);
}
