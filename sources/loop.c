/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:35:23 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/07 09:39:03 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <threads.h>
#include "philosophers.h"

static
int	stt_update_clock(long delay, const atomic_long *time_now)
{
	static thread_local long	cur_time = 0;
	long						dt;
	long						prev_time;

	while (delay >= 0 && cur_time >= 0)
	{
		prev_time = cur_time;
		cur_time = *time_now;
		while (cur_time == prev_time)
		{
			usleep((delay >> (1 + (delay < 1000))) + 1);
			cur_time = *time_now;
		}
		dt = (cur_time - prev_time);
		delay -= dt;
	}
	return (cur_time < 0);
}

static inline
int	stt_change_state(uint8_t new_state, t_philo *ph, long delay)
{
	if (stt_update_clock(0, ph->time_now))
		return (1);
	if (new_state == e_eat)
		*ph->last_meal = *ph->time_now;
	*ph->state = new_state;
	if (stt_update_clock(delay, ph->time_now))
		return (1);
	return (0);
}

static inline
void	stt_delay_eating(t_philo *ph)
{
	long	time_left;
	long	time_slack;

	time_left = ph->params.death - (*ph->time_now - *ph->last_meal);
	time_slack = time_left - ph->params.eat;
	if (time_slack > 0)
		stt_update_clock(time_slack, ph->time_now);
	return ;
}

static inline
int	stt_philo_init(t_philo *ph)
{
	while (*ph->time_now == 0)
		usleep(FT_TICK_INTERVAL);
	*ph->last_meal = *ph->time_now;
	if (ph->index & 1)
		stt_update_clock(ph->params.eat / 2, ph->time_now);
	if (ph->index == ph->params.count)
	{
		take_fork(ph->forks[0]);
		stt_change_state(e_fork0, ph, 0);
		return (1);
	}
	return (0);
}

int	philo_loop(t_philo *ph)
{
	if (stt_philo_init(ph))
		return (1);
	while (ph->params.eat_count > 0)
	{
		take_fork(ph->forks[ph->index & 1]);
		if (stt_change_state(e_fork0, ph, 0))
			return (1);
		take_fork(ph->forks[!(ph->index & 1)]);
		if (stt_change_state(e_fork1, ph, 0))
			return (1);
		if (stt_change_state(e_eat, ph, ph->params.eat))
			return (1);
		ph->params.eat_count--;
		drop_forks(ph->forks[0], ph->forks[1]);
		if (stt_change_state(e_sleep, ph, ph->params.sleep))
			return (1);
		if (stt_change_state(e_idle, ph, 0))
			return (1);
		stt_delay_eating(ph);
	}
	stt_change_state(e_done, ph, 0);
	return (0);
}
