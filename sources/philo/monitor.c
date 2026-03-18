/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:01:35 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/06 08:17:54 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/time.h>
#include <unistd.h>
#include "philosophers_mandatory.h"

// num_ph, die, eat, sleep, eat_count
static inline
int	stt_print_state(uint8_t state, size_t index, long time_now)
{
	char				buffer[64];
	const char			*tstr = ft_itoa_r(time_now / 1000, buffer + 31);
	const char			*istr = ft_itoa_r((int64_t)index + 1, buffer + 63);
	static const char	*msg[7] = {" died", " is thinking", " has taken a fork",
		" has taken a fork", " is eating", " is sleeping", NULL};
	const char			*msg_vec[5] = {tstr, " ", istr, msg[state], NULL};

	ft_writev(STDOUT_FILENO, msg_vec, '\n');
	return (state);
}

// Returns 0 on death or done
static inline
int	stt_get_state(t_sim_cfg *cfg, long time_now)
{
	size_t		i;
	size_t		done_count;
	uint8_t		cur_state;

	i = 0;
	done_count = 0;
	while (i < cfg->params.count)
	{
		cur_state = cfg->state[i];
		if (cur_state == e_done)
		{
			done_count++;
			i++;
			continue ;
		}
		if (cur_state != cfg->prev_state[i])
			cfg->prev_state[i] = stt_print_state(cur_state, i, time_now);
		if (time_now - cfg->last_meal[i] > cfg->params.death)
			return (stt_print_state(0, i, time_now));	// DED
		i++;
	}
	return (done_count != cfg->params.count);
}

int	monitor_state(t_sim_cfg *cfg)
{
	long			prev_time;
	long			dt;
	struct timeval	now;

	gettimeofday(&now, NULL);
	prev_time = now.tv_sec * 1000000 + now.tv_usec;
	while (stt_get_state(cfg, cfg->time_now))
	{
		usleep(FT_TICK_INTERVAL);
		gettimeofday(&now, NULL);
		dt = (1000000 * now.tv_sec + now.tv_usec) - prev_time;
		cfg->time_now += dt;
		prev_time += dt;
	}
	return (0);
}
