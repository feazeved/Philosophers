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

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(t_table));
	if (parse_args(&table, argc, argv))
		return (EXIT_FAILURE);
	if (init_table(&table))
		return (EXIT_FAILURE);
	start_simulation();
	stt_cleanup(&table);
	return (EXIT_SUCCESS);
}
