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

static void	stt_join_philos(t_table *table, int32_t count)
{
	int32_t	i;

	i = 0;
	while (i < count)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

static int	stt_start_simulation(t_table *table)
{
	int32_t		i;
	pthread_t	monitor;

	i = 0;
	while (i < table->number_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				philo_routine, &table->philos[i]))
		{
			stt_join_philos(table, i);
			return (1);
		}
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, table))
	{
		stt_join_philos(table, table->number_philos);
		return (1);
	}
	i = 0;
	stt_join_philos(table, table->number_philos);
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
		cleanup(&table, 0);
		return (EXIT_FAILURE);
	}
	cleanup(&table, 0);
	return (EXIT_SUCCESS);
}
