/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:55:08 by feazeved          #+#    #+#             */
/*   Updated: 2026/04/27 20:25:37 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>
#include <stdio.h>

static void	stt_print_state(t_philo *philo, const char *state)
{
	int64_t	time_ms;

	sem_wait(philo->table->print_sem);
	time_ms = get_time_ms() - philo->table->start_time;
	printf("%lld %d %s\n", (long long)time_ms, philo->id, state);
	sem_post(philo->table->print_sem);
}

static void	stt_eat(t_philo *philo)
{
	sem_wait(philo->table->meal_sem);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	sem_post(philo->table->meal_sem);
	stt_print_state(philo, "is eating");
	precise_sleep(philo->table->eat_time, philo->table);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
	if (philo->table->number_meals != -1
			&& philo->meals_eaten >= philo->table->number_meals)
	{
		sem_post(philo->table->full_sem);
		exit(0);
	}
}

void	*philo_process(t_philo *philo)
{
	if (pthread_create(&philo->monitor_thread, NULL, monitor_routine, philo))
		exit(1);
	pthread_detach(philo->monitor_thread);
	if (philo->id % 2 == 0)
		precise_sleep(philo->table->eat_time / 2, philo->table);
	while (1)
	{
		stt_print_state(philo, "is thinking");
		sem_wait(philo->table->forks);
		stt_print_state(philo, "has taken a fork");
		sem_wait(philo->table->forks);
		stt_print_state(philo, "has taken a fork");
		stt_eat(philo);
		stt_print_state(philo, "is sleeping");
		precise_sleep(philo->table->sleep_time, philo->table);
	}
	exit(0);
}
