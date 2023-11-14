/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:59:58 by rluiz             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/11/14 15:07:53 by rluiz            ###   ########.fr       */
=======
/*   Updated: 2023/11/14 01:51:53 by rluiz            ###   ########.fr       */
>>>>>>> 1dcffa4e79bae235108ca57daa60a8cb5e346dc6
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <pthread.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef struct s_arena
{
	void				*buf;
	size_t				buf_size;
	size_t				prev_offset;
	size_t				curr_offset;
}						t_arena;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
	int					is_taken;
}						t_fork;

typedef struct s_philo
{
	int					id;
	int					meals;
	int					is_eating;
	int					is_dead;
	int					is_full;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_meals;
	int					num_of_philos;
	int					time_start;
	int					time_last_meal;
	t_fork				*left_fork;
	t_fork				*right_fork;
	t_table				*table;
	pthread_mutex_t		*death_mutex;
	pthread_mutex_t		*eat_mutex;
	pthread_mutex_t		*sleep_mutex;
	pthread_mutex_t		*think_mutex;
	pthread_mutex_t		*fork_mutex;
	pthread_t			philo_thread_id;
}						t_philo;

typedef struct s_table
{
	int					num_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_meals;
	int					time_start;
	int					philos_full;
	int					philo_dead;
	t_philo				*philos;
	t_fork				*forks;
	t_arena				*arena;
	pthread_mutex_t		*death_mutex;
	pthread_mutex_t		*table_mutex;
	pthread_mutex_t		*print_mutex;
}						t_table;

void					*arena_init(size_t buffer_size);
void					arena_reset(t_arena *a);
void					*arena_alloc(t_arena *a, size_t size);
void					arena_destroy(t_arena *a);
void					error_exit(char *error, pthread_mutex_t *print,
							t_arena *arena);
void					ft_printf(t_table *table, const char *src, ...);
int						ft_atoi(const char *str);
char					*ft_itoa(t_arena *arena, int n);
int						get_time_ms(t_table *table);
void					ft_putstr_fd(char *s, int fd);
void					ft_putchar_fd(char c, int fd);
void					*philo_life(void *philo);
void					check_and_exec(int (*func)(t_philo), t_table *table, int id);

#endif