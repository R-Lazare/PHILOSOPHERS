/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifeutils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:41:36 by rluiz             #+#    #+#             */
/*   Updated: 2023/11/23 18:16:41 by rluiz            ###   ########.fr       */
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

void	check_exit(t_philo *philo)
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
}