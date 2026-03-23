/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:55:08 by feazeved          #+#    #+#             */
/*   Updated: 2026/03/11 18:30:41 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Return value: 0) Success  1) Error
static int	stt_init_forks(t_table *table)
{
	int32_t	i;

	i = 0;
	while (i < table->number_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

static void	stt_assign_forks(t_philo *philo, t_table *table)
{
	int32_t	id;

	id = philo->id - 1;
	if (philo->id % 2 != 0)
	{
		philo->left_fork = &table->forks[id];
		philo->right_fork = &table->forks[(id + 1) % table->number_philos];
	}
	else
	{
		philo->left_fork = &table->forks[(id + 1) % table->number_philos];
		philo->right_fork = &table->forks[id];
	}
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
		stt_assign_forks(&table->philos[i], table);
		i++;
	}
}

// Return value: 0) Success  1) Error
int	init_table(t_table *table)
{
    table->start_time = get_time_ms();
	if (pthread_mutex_init(&table->death_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&table->print_mutex, NULL))
		return (1);
	if (stt_init_forks(table))
		return (1);
	stt_init_philos(table);
	return (0);
}