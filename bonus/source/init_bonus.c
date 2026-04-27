/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:55:08 by feazeved          #+#    #+#             */
/*   Updated: 2026/04/27 18:18:29 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	stt_init_semaphores(t_table *table)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_death");
	sem_unlink("/philo_meal");
	table->forks = sem_open("/philo_forks", O_CREAT, 0644, table->number_philos);
	table->print_sem = sem_open("/philo_print", O_CREAT, 0644, 1);
	table->death_sem = sem_open("/philo_death", O_CREAT, 0644, 0);
	table->meal_sem = sem_open("/philo_meal", O_CREAT, 0644, 1);
	if (table->forks == SEM_FAILED || table->print_sem == SEM_FAILED
			|| table->death_sem == SEM_FAILED || table->meal_sem == SEM_FAILED)
	{
		cleanup_semaphores(table);
		return (1);
	}
	return (0);
}

static void	stt_init_philos(t_table *table)
{
	int32_t	i;

	i = 0;
	while (i < table->number_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = table->start_time;
		table->philos[i].table = table;
		i++;
	}
}

// Return value: 0) Success  1) Error
int	init_table(t_table *table)
{
    table->start_time = get_time_ms();
	if (stt_init_semaphores(table))
		return (1);
	stt_init_philos(table);
	return (0);
}