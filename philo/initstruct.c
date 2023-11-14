/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initstruct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:00:39 by rluiz             #+#    #+#             */
/*   Updated: 2023/11/14 16:55:01 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*parse(t_arena *arena, int argc, char **argv)
{
	t_table	*table;

	table = (t_table *)arena_alloc(arena, sizeof(t_table));
	table->arena = arena;
	table->time_start = 0;
	table->time_start = get_time_ms(table);
	table->print_mutex = (pthread_mutex_t *)arena_alloc(table->arena, 20);
	pthread_mutex_init(table->print_mutex, NULL);
	if (argc != 6 && argc != 5)
		error_exit("Error: Wrong number of arguments\n", table->print_mutex, arena);
	table->num_of_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->num_of_meals = ft_atoi(argv[5]);
	else if (argc == 5)
		table->num_of_meals = -1;
	if (!check_args(argc, argv))
		error_exit("Error: Wrong arguments\n", table->print_mutex, arena);
	table->philo_dead = 0;
	return (table);
}

int	check_helper(t_philo *philo2)
{
	ft_printf(philo2->table, "%d ms %d died\n", get_time_ms(philo2->table),
		philo2->id);
	pthread_mutex_lock(philo2->table->death_mutex);
	philo2->table->philo_dead = 1;
	pthread_mutex_unlock(philo2->table->death_mutex);
	if (philo2->is_eating != 0)
	{
		if (philo2->table->num_of_philos != 1)
		{
			if (philo2->is_eating == 1 && philo2->id % 2 == 0)
				pthread_mutex_unlock(&(philo2->right_fork->fork));
			else if (philo2->is_eating == 1 && philo2->id % 2 == 1)
				pthread_mutex_unlock(&(philo2->left_fork->fork));
			else if (philo2->is_eating == 2)
			{
				pthread_mutex_unlock(&(philo2->left_fork->fork));
				pthread_mutex_unlock(&(philo2->right_fork->fork));
			}
		}
		else
			pthread_mutex_unlock(&(philo2->right_fork->fork));
	}
	pthread_mutex_unlock(philo2->table->table_mutex);
	return (0);
}
