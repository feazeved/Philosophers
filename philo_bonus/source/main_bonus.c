/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:55:08 by feazeved          #+#    #+#             */
/*   Updated: 2026/04/27 19:42:28 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "philo_bonus.h"

static void	*stt_wait_all_ate(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	i = 0;
	while (i < table->number_philos)
	{
		waitpid(table->pids[i], NULL, 0);
		i++;
	}
	sem_post(table->death_sem);
	return (NULL);
}

static void	stt_kill_all(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_philos)
		kill(table->pids[i], SIGKILL);
}

static int	stt_start_simulation(t_table *table)
{
	int			i;
	pthread_t	waiter;

	i = -1;
	while (++i < table->number_philos)
	{
		table->pids[i] = fork();
		if (table->pids[i] < 0)
		{
			stt_kill_all(table);
			return (1);
		}
		if (table->pids[i] == 0)
			philo_process(&table->philos[i]);
	}
	if (pthread_create(&waiter, NULL, stt_wait_all_ate, table))
	{
		stt_kill_all(table);
		return (1);
	}
	sem_wait(table->death_sem);
	stt_kill_all(table);
	pthread_join(waiter, NULL);
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
		write(STDERR_FILENO, "Error: semaphores initialization failed.\n", 41);
		return (EXIT_FAILURE);
	}
	if (stt_start_simulation(&table))
	{
		write(STDERR_FILENO, "Error: fork failed.\n", 20);
		cleanup_semaphores(&table);
		return (EXIT_FAILURE);
	}
	cleanup_semaphores(&table);
	return (EXIT_SUCCESS);
}
