/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:59:58 by rluiz             #+#    #+#             */
/*   Updated: 2023/11/13 19:02:43 by rluiz            ###   ########.fr       */
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

#endif