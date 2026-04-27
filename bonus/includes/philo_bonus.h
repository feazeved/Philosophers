/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:55:08 by feazeved          #+#    #+#             */
/*   Updated: 2026/04/27 20:23:04 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define MAX_PHILOS 200
# define FT_USAGE "Error: Usage: Check correct usage on README.\n"
# define FT_INVALID_ARG "Error: An argument is invalid.\n"

# include <stdint.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <signal.h>

typedef struct	s_table	t_table;

typedef struct	s_philo
{
	int32_t		id;
	int32_t		meals_eaten;
	int64_t		last_meal_time;
	pthread_t	monitor_thread;
	t_table		*table;
}	t_philo;

typedef struct	s_table
{
	int32_t	number_philos;
	int32_t	eat_time;
	int32_t	starve_time;
	int32_t	sleep_time;
	int32_t	number_meals;
	int64_t	start_time;
	int8_t	dead;
	t_philo	philos[MAX_PHILOS];
	pid_t	pids[MAX_PHILOS];
	sem_t	*forks;
	sem_t	*print_sem;
	sem_t	*death_sem;
	sem_t	*meal_sem;
	sem_t	*full_sem;
}	t_table;

void    *monitor_routine(void *arg);
void	*philo_process(t_philo *philo);
int		parse_args(t_table *table, int argc, char **argv);
int		init_table(t_table *table);
void	cleanup_semaphores(t_table *table);
int64_t	get_time_ms(void);
void	precise_sleep(int64_t duration_ms, t_table *table);

#endif