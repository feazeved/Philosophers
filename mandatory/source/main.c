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

#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "philo.h"

static void	stt_cleanup(t_table *table)
{
	int32_t	i;

	i = 0;
	while (i < table->number_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->print_mutex);
}

static int	stt_start_simulation(t_table *table)
{
	int32_t		i;
	pthread_t	monitor;

	i = 0;
	while (i < table->number_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philo_routine, &table->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, table))
		return (1);
	i = 0;
	while (i < table->number_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(t_table));
	if (parse_args(&table, argc, argv))
		return (EXIT_FAILURE);
	if (init_table(&table))
	{
		write(STDERR_FILENO, "Error: mutex initialization failed.\n", 36);
		return (EXIT_FAILURE);
	}
	if (stt_start_simulation(&table))
	{
		write(STDERR_FILENO, "Error: thread creation failed.\n", 31);
		stt_cleanup(&table);
		return (EXIT_FAILURE);
	}
	stt_cleanup(&table);
	return (EXIT_SUCCESS);
}
