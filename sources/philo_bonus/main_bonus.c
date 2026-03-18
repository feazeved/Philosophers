/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:21:09 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/07 11:54:59 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <fcntl.h>
#include <semaphore.h>
#include "philosophers_bonus.h"

static
int	stt_philo_start(size_t index, t_params params, const char *sem_name)
{
	t_philo			ph;
	t_thread_cfg	cfg;
	pthread_t		thread_id;
	sem_t			*sem;

	cfg = (t_thread_cfg){.index = index, .params = params, .time_now = 0,
		.last_meal = 0, .state = e_idle};
	sem = sem_open(sem_name, 0);
	if (sem == SEM_FAILED)
	{
		write(STDERR_FILENO, "init_error: semaphore failed\n", 29);
		return (1);
	}
	ph = (t_philo){cfg.index, cfg.params, &cfg.time_now,
		&cfg.last_meal, &cfg.state, {sem, sem}};
	if (pthread_create(&thread_id, NULL, monitor_start, &cfg)
		|| pthread_detach(thread_id))
	{
		write(STDERR_FILENO, "init_error: thread failure\n", 27);
		return (1);
	}
	philo_loop(&ph);
	while (true)
		usleep(10000);
	return (1);
}

static int	\
stt_let_there_be_life(t_params params, pid_t *cpid_list, const char *sem_name)
{
	size_t	count;
	pid_t	process_id;

	count = 0;
	while (count < params.count)
	{
		process_id = fork();
		if (process_id == 0)
			exit(stt_philo_start(count, params, sem_name));
		else if (process_id > 0)
			cpid_list[count] = process_id;
		else
		{
			philo_extinction(cpid_list, count);
			write(STDERR_FILENO, "init_error: fork failure\n", 25);
			return (1);
		}
		count++;
	}
	philo_wait(cpid_list, params.count);
	return (0);
}

// num_ph, die, eat, sleep, eat_count
int	main(int argc, const char **argv)
{
	int			rvalue;
	t_params	params;
	sem_t		*sem;
	const char	sem_name[8] = "__forks";
	pid_t		cpid_list[FT_MAX_PHILO];

	rvalue = 0;
	if (init_params(argc, argv, &params) != 0)
		return (1);
	sem_unlink(sem_name);
	sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, params.count);
	if (sem == SEM_FAILED)
	{
		write(STDERR_FILENO, "init_error: semaphore failed\n", 29);
		return (1);
	}
	if (stt_let_there_be_life(params, cpid_list, sem_name))
		rvalue = 1;
	sem_close(sem);
	sem_unlink(sem_name);
	return (rvalue);
}
