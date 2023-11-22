/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initstruct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:00:39 by rluiz             #+#    #+#             */
/*   Updated: 2023/11/22 17:05:03 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		return (0);
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		return (0);
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		return (0);
	return (1);
}

t_table	*parse(t_arena *arena, int argc, char **argv)
{
	t_table	*table;

	table = (t_table *)arena_alloc(arena, sizeof(t_table));
	table->arena = arena;
	table->time_start = 0;
	table->print_mutex = (pthread_mutex_t *)arena_alloc(table->arena, sizeof(pthread_mutex_t));
	pthread_mutex_init(table->print_mutex, NULL);
	if (argc != 6 && argc != 5)
		error_exit("Error: Wrong number of arguments\n", table->print_mutex,
			arena);
	table->num_of_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->num_of_meals = ft_atoi(argv[5]);
	else if (argc == 5)
		table->num_of_meals = 2147483647;
	if (!check_args(argc, argv))
		error_exit("Error: Wrong arguments\n", table->print_mutex, arena);
	table->philo_dead = 0;
	return (table);
}

void	init_forks(t_table *table)
{
	t_fork	*forks;
	int		i;

	i = 0;
	forks = (t_fork *)arena_alloc(table->arena, sizeof(t_fork) * table->num_of_philos);
	while (i < table->num_of_philos)
	{
		forks[i].fork_id = i + 1;
		forks[i].is_taken = 0;
		forks[i].fork_taken = (pthread_mutex_t *)arena_alloc(table->arena, 20);
		pthread_mutex_init(forks[i].fork_taken, NULL);
		forks[i].fork = (pthread_mutex_t *)arena_alloc(table->arena, 20);
		pthread_mutex_init(forks[i].fork, NULL);
		table->philos[i].right_fork = forks + i;
		if (i != table->num_of_philos - 1 && table->num_of_philos != 1)
			table->philos[i + 1].left_fork = forks + i;
		else if (i == table->num_of_philos - 1 && table->num_of_philos != 1)
			table->philos[0].left_fork = forks + i;
		i++;
	}
	table->forks = forks;
	table->time_mutex = (pthread_mutex_t *)arena_alloc(table->arena, 20);
	pthread_mutex_init(table->time_mutex, NULL);
	table->time_start = get_time_ms(table);
}

void	init_philo(t_table *table)
{
	int	i;

	table->philos = (t_philo *)arena_alloc(table->arena,
			sizeof(t_philo) * table->num_of_philos);
	table->death_mutex = (pthread_mutex_t *)arena_alloc(table->arena, 20);
	pthread_mutex_init(table->death_mutex, NULL);
	table->table_mutex = (pthread_mutex_t *)arena_alloc(table->arena, 20);
	pthread_mutex_init(table->table_mutex, NULL);
	i = -1;
	while (++i < table->num_of_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].is_eating = 0;
		table->philos[i].is_dead = 0;
		table->philos[i].is_full = 0;
		table->philos[i].meals = 0;
		table->philos[i].time_last_meal = 0;
		table->philos[i].table = table;
		table->philos[i].death_mutex = table->death_mutex;
		table->philos[i].eat_mutex = table->table_mutex;
		table->philos[i].fork_mutex = (pthread_mutex_t *)arena_alloc(table->arena, 20);
		pthread_mutex_init(table->philos[i].fork_mutex, NULL);
	}
	return (init_forks(table));
}
