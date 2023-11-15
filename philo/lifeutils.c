/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifeutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:00:41 by rluiz             #+#    #+#             */
/*   Updated: 2023/11/15 18:14:19 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_and_exec(void (*func)(t_philo *), t_table *table, int id)
{
	pthread_mutex_lock(table->death_mutex);
	if (table->philo_dead || table->philos_full)
	{
		pthread_mutex_unlock(table->death_mutex);
		if (id % 2 == 0)
		{
			pthread_mutex_lock(table->philos[id].right_fork->fork_taken);
			if (table->philos[id - 1].right_fork->is_taken != 0)
				pthread_mutex_unlock(table->philos[id].right_fork->fork);
			pthread_mutex_unlock(table->philos[id].right_fork->fork_taken);
			pthread_mutex_lock(table->philos[id].left_fork->fork_taken);
			if (table->philos[id - 1].left_fork->is_taken != 0 )
				pthread_mutex_unlock(table->philos[id].left_fork->fork);
		}
		else if (id % 2 == 1)
		{
			pthread_mutex_lock(table->philos[id].left_fork->fork_taken);
			if (table->philos[id + 1].left_fork->is_taken != 0)
				pthread_mutex_unlock(table->philos[id].left_fork->fork);
			pthread_mutex_unlock(table->philos[id].left_fork->fork_taken);
			pthread_mutex_lock(table->philos[id].right_fork->fork_taken);
			if (table->philos[id + 1].right_fork->is_taken != 0)
				pthread_mutex_unlock(table->philos[id].right_fork->fork);
			pthread_mutex_unlock(table->philos[id].right_fork->fork_taken);
		}
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(table->death_mutex);
	func(&(table->philos[id]));
}

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		//pthread_mutex_lock(philo->left_fork->fork_taken);
		pthread_mutex_lock(philo->right_fork->fork_taken);
	}
	else if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->right_fork->fork_taken);
		//pthread_mutex_lock(philo->left_fork->fork_taken);
	}
	if (philo->right_fork->is_taken == philo->id
		&& philo->left_fork->is_taken == philo->id)
	{
		//pthread_mutex_unlock(philo->left_fork->fork_taken);
		//pthread_mutex_unlock(philo->right_fork->fork_taken);
		pthread_mutex_lock(philo->eat_mutex);
		philo->time_last_meal = get_time_ms(philo->table);
		ft_printf(philo->table, "%d ms %d is eating\n",
			get_time_ms(philo->table), philo->id);
		usleep(philo->table->time_to_eat * 1000);
		philo->meals++;
		pthread_mutex_lock(philo->right_fork->fork_taken);
		//pthread_mutex_lock(philo->left_fork->fork_taken);
		philo->right_fork->is_taken = 0;
		philo->left_fork->is_taken = 0;
		pthread_mutex_unlock(philo->left_fork->fork);
		pthread_mutex_unlock(philo->right_fork->fork);
		pthread_mutex_unlock(philo->eat_mutex);
	}
	//pthread_mutex_unlock(philo->right_fork->fork_taken);
	//pthread_mutex_unlock(philo->left_fork->fork_taken);
}

void	philo_lock1(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		//pthread_mutex_lock(philo->left_fork->fork_taken);
		if (!philo->left_fork->is_taken)
		{
			pthread_mutex_lock(philo->left_fork->fork);
			philo->left_fork->is_taken = philo->id;
		}
		//pthread_mutex_unlock(philo->left_fork->fork_taken);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork->fork_taken);
		if (!philo->right_fork->is_taken)
		{
			pthread_mutex_lock(philo->right_fork->fork);
			philo->right_fork->is_taken = philo->id;
		}
		//pthread_mutex_unlock(philo->right_fork->fork_taken);
	}
}

void	philo_lock2(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->right_fork->fork_taken);
		if (!philo->right_fork->is_taken)
		{
			pthread_mutex_lock(philo->right_fork->fork);
			philo->right_fork->is_taken = philo->id;
		}
		//pthread_mutex_unlock(philo->right_fork->fork_taken);
	}
	else
	{
		//pthread_mutex_lock(philo->left_fork->fork_taken);
		if (!philo->left_fork->is_taken)
		{
			pthread_mutex_lock(philo->left_fork->fork);
			philo->left_fork->is_taken = philo->id;
		}
		//pthread_mutex_unlock(philo->left_fork->fork_taken);
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
		check_and_exec(&philo_lock1, philo2->table, philo2->id);
		check_and_exec(&philo_lock2, philo2->table, philo2->id);
		check_and_exec(&philo_eat, philo2->table, philo2->id);
		check_and_exec(&philo_sleep_think, philo2->table, philo2->id);
	}
	return (NULL);
}
