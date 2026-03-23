/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:54:17 by feazeved          #+#    #+#             */
/*   Updated: 2026/03/11 17:54:59 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAX_PHILOS 200

# define FT_USAGE "Error: Usage: Check correct usage on README\n"

# define FT_INVALID_ARG "Error: An argument is negative or non numeric.\n"

# define FT_EMPTY_ARG "Error: An argument is empty.\n"

# define FT_OVERFLOW "Error: An argument is bigger than int max.\n"

# include <stdint.h>
# include <pthread.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int32_t			id;
	int32_t			meals_eaten;
	int64_t			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
}	t_philo;

typedef struct	s_table
{
	int32_t			number_philos;
	int32_t			eat_time;
	int32_t			starve_time;
	int32_t			sleep_time;
	int32_t			number_meals;
	int64_t			start_time;
	int8_t			dead;
	t_philo			philos[MAX_PHILOS];
	pthread_mutex_t	forks[MAX_PHILOS];
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
}	t_table;

int		parse_args(t_table *table, int argc, char **argv);
int64_t	get_time_ms(void);
int		init_table(t_table *table);

#endif