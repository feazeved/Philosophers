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

#include <sys/time.h>
#include <stdint.h>
#include "philo.h"

int64_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (((int64_t)tv.tv_sec * 1000) + ((int64_t)tv.tv_usec / 1000));
}
void	precise_sleep(int64_t duration_ms, t_table *table)
{
	int64_t	start;

	start = get_time_ms();
	while (!is_dead(table))
	{
		if (get_time_ms() - start >= duration_ms)
			break ;
		usleep(500);
	}
}

int8_t	is_dead(t_table *table)
{
	int8_t	dead;

	pthread_mutex_lock(&table->death_mutex);
	dead = table->dead;
	pthread_mutex_unlock(&table->death_mutex);
	return (dead);
}

void	print_state(t_philo *philo, const char *state)
{
	int64_t	time_ms;

	pthread_mutex_lock(&philo->table->print_mutex);
	time_ms = get_time_ms() - philo->table->start_time;
	if (!philo->table->dead)
		printf("%lld %d %s\n", time_ms, philo->id, state);
	pthread_mutex_unlock(&philo->table->print_mutex);
}