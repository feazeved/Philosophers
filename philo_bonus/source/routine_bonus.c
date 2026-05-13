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

static void	stt_clean_child(t_table *table)
{
	if (table->eat_mut != SEM_FAILED)
		sem_close(table->eat_mut);
	if (table->forks != SEM_FAILED)
		sem_close(table->forks);
	if (table->print_sem != SEM_FAILED)
		sem_close(table->print_sem);
	if (table->death_sem != SEM_FAILED)
		sem_close(table->death_sem);
	if (table->meal_sem != SEM_FAILED)
		sem_close(table->meal_sem);
}

static int	stt_eat(t_philo *philo)
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
		return (1);
	return (0);
}

static void	*stt_single_philo(t_philo *philo)
{
	sem_wait(philo->table->forks);
	stt_print_state(philo, "has taken a fork");
	precise_sleep(philo->table->starve_time + 10, philo->table);
	stt_clean_child(philo->table);
	exit(0);
}

void	*philo_process(t_philo *philo)
{
	sem_wait(philo->table->meal_sem);
	philo->last_meal_time = get_time_ms();
	sem_post(philo->table->meal_sem);
	if (pthread_create(&philo->monitor_thread, NULL, monitor_routine, philo))
		exit(1);
	if (philo->table->number_philos == 1)
		stt_single_philo(philo);
	while (1)
	{
		stt_print_state(philo, "is thinking");
		sem_wait(philo->table->eat_mut);
		sem_wait(philo->table->forks);
		stt_print_state(philo, "has taken a fork");
		sem_wait(philo->table->forks);
		stt_print_state(philo, "has taken a fork");
		sem_post(philo->table->eat_mut);
		if (stt_eat(philo))
			break ;
		stt_print_state(philo, "is sleeping");
		precise_sleep(philo->table->sleep_time, philo->table);
	}
	philo->stop_monitor = 1;
	pthread_join(philo->monitor_thread, NULL);
	stt_clean_child(philo->table);
	exit(0);
}
