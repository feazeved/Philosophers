/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:21:09 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/07 09:58:56 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include "philosophers_mandatory.h"

static
void	*stt_philo_start(void *varg)
{
	philo_loop((t_philo *)varg);
	return (NULL);
}

static
int	stt_let_there_be_life(size_t index, t_sim_cfg *cfg)
{
	static t_philo	philo[FT_MAX_PHILO];
	pthread_t		thread_id;

	philo[index] = (t_philo){.index = index, .params = cfg->params,
		.time_now = &cfg->time_now, .state = cfg->state + index,
		.last_meal = cfg->last_meal + index,
		.forks = {cfg->mutex + index,
		cfg->mutex + (index + 1) % cfg->params.count}};
	cfg->prev_state[index] = e_idle;
	cfg->state[index] = e_idle;
	cfg->last_meal[index] = 0;
	if (pthread_create(&thread_id, NULL, stt_philo_start, philo + index))
		return (1);
	if (pthread_detach(thread_id))
		return (1);
	return (0);
}

int	main(int argc, const char **argv)
{
	size_t				i;
	static t_sim_cfg	cfg;

	cfg.time_now = 0;
	if (init_params(argc, argv, &cfg.params) != 0)
		return (1);
	i = 0;
	while (i < cfg.params.count)
	{
		if (pthread_mutex_init(cfg.mutex + i++, NULL))
		{
			write(STDERR_FILENO, "init_error: mutex failure\n", 26);
			return (1);
		}
	}
	i = 0;
	while (i < cfg.params.count)
	{
		if (stt_let_there_be_life(i++, &cfg))
		{
			write(STDERR_FILENO, "init_error: thread failure\n", 27);
			return (1);
		}
	}
	return (monitor_state(&cfg));
}
