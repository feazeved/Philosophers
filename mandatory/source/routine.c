/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:55:08 by feazeved          #+#    #+#             */
/*   Updated: 2026/03/11 18:30:41 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int8_t	stt_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (is_dead(philo->table))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	if (is_dead(philo->table))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_state(philo, "has taken a fork");
	return (0);
}

static void	stt_put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	stt_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_mutex);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->death_mutex);
	print_state(philo, "is eating");
	precise_sleep(philo->table->eat_time, philo->table);
}

static void	*stt_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	precise_sleep(philo->table->starve_time, philo->table);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->number_philos == 1)
		return (stt_single_philo(philo));
	if (philo->id % 2 == 0)
		precise_sleep(philo->table->eat_time / 2, philo->table);
	while (!is_dead(philo->table))
	{
		print_state(philo, "is thinking");
		if (stt_take_forks(philo))
			return (NULL);
		stt_eat(philo);
		stt_put_forks(philo);
		print_state(philo, "is sleeping");
		precise_sleep(philo->table->sleep_time, philo->table);
	}
	return (NULL);
}