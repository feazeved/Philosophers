/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:40:50 by feazeved          #+#    #+#             */
/*   Updated: 2026/03/26 18:41:44 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

static int8_t	stt_check_death(t_philo *philo)
{
	int64_t	elapsed;
	int64_t	current_time;

	pthread_mutex_lock(&philo->table->death_mutex);
	elapsed = get_time_ms() - philo->last_meal_time;
	if (elapsed > philo->table->starve_time)
	{
		philo->table->dead = 1;
		pthread_mutex_lock(&philo->table->print_mutex);
		current_time = get_time_ms() - philo->table->start_time;
		printf("%lld %d %s\n", (long long)current_time, philo->id, "died");
		pthread_mutex_unlock(&philo->table->print_mutex);
		pthread_mutex_unlock(&philo->table->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->death_mutex);
	return (0);
}
 
static int8_t   stt_check_all_ate(t_table *table)
{
    int32_t i;
    int32_t full;
 
    if (table->number_meals == -1)
        return (0);
    i = 0;
    full = 0;
    pthread_mutex_lock(&table->death_mutex);
    while (i < table->number_philos)
    {
        if (table->philos[i].meals_eaten >= table->number_meals)
            full++;
		i++;
    }
    pthread_mutex_unlock(&table->death_mutex);
	if (full == table->number_philos)
	{
		pthread_mutex_lock(&table->death_mutex);
		table->dead = 1;
		pthread_mutex_unlock(&table->death_mutex);
		return (1);
	}
	return (0);
}
 
void    *monitor_routine(void *arg)
{
    t_table *table;
    int32_t i;
 
    table = (t_table *)arg;
    while (1)
    {
        i = 0;
        while (i < table->number_philos)
        {
            if (stt_check_death(&table->philos[i]))
                return (NULL);
            i++;
        }
        if (stt_check_all_ate(table))
            return (NULL);
        usleep(1000);
    }
    return (NULL);
}

