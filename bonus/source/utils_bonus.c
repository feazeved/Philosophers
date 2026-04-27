/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:55:08 by feazeved          #+#    #+#             */
/*   Updated: 2026/04/27 19:33:46 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdint.h>
#include <unistd.h>
#include "philo_bonus.h"

int64_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (((int64_t)tv.tv_sec * 1000) + ((int64_t)tv.tv_usec / 1000));
}

void	precise_sleep(int64_t duration_ms, t_table *table)
{
	int64_t	start;

	(void)table;
	start = get_time_ms();
	while ((get_time_ms() - start) < duration_ms)
	{
		usleep(500);
	}
}

void	cleanup_semaphores(t_table *table)
{
	if (table->forks != SEM_FAILED)
		sem_close(table->forks);
	if (table->print_sem != SEM_FAILED)
		sem_close(table->print_sem);
	if (table->death_sem != SEM_FAILED)
		sem_close(table->death_sem);
	if (table->meal_sem != SEM_FAILED)
		sem_close(table->meal_sem);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_death");
	sem_unlink("/philo_meal");
}