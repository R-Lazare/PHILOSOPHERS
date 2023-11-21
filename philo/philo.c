/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:00:43 by rluiz             #+#    #+#             */
/*   Updated: 2023/11/21 18:31:20 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_full(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philos)
	{
		pthread_mutex_lock(table->philos[i].eat_mutex);
		if (table->philos[i].meals < table->num_of_meals)
		{
			pthread_mutex_unlock(table->philos[i].eat_mutex);
			return (0);
		}
		pthread_mutex_unlock(table->philos[i].eat_mutex);
	}
	ft_printf(table, "All philos ate %d times\n", table->num_of_meals);
	pthread_mutex_lock(table->death_mutex);
	table->philos_full = 1;
	pthread_mutex_unlock(table->death_mutex);
	return (1);
}

int	check_one_dead(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philos)
	{
		pthread_mutex_lock(table->philos[i].eat_mutex);
		if (get_time_ms(table)
			- table->philos[i].time_last_meal > table->time_to_die)
		{
			pthread_mutex_unlock(table->philos[i].eat_mutex);
			ft_printf(table, "%d ms %d died\n", get_time_ms(table),
				table->philos[i].id);
			pthread_mutex_lock(table->death_mutex);
			table->philo_dead = 1;
			pthread_mutex_unlock(table->death_mutex);
			return (1);
		}
		pthread_mutex_unlock(table->philos[i].eat_mutex);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table *table;
	t_arena *arena;
	int i;

	arena = arena_init(1000000);
	table = parse(arena, argc, argv);
	init_philo(table);
	i = -1;
	while (++i < table->num_of_philos)
		pthread_create(&table->philos[i].philo_thread_id, NULL, philo_life,
			&table->philos[i]);
	while (1)
	{
		if (table->philo_dead || check_one_dead(table))
			break ;
		if (check_all_full(table))
			break ;
	}
	i = -1;
	while (++i < table->num_of_philos)
		pthread_join(table->philos[i].philo_thread_id, NULL);
	arena_destroy(arena);
	return (0);
}