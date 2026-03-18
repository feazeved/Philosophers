/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_mandatory.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:21:18 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/06 11:31:10 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_MANDATORY_H
# define PHILOSOPHERS_MANDATORY_H

# include <stdint.h>
# include <stddef.h>
# include <stdatomic.h>
# include <pthread.h>
# include <unistd.h>
# include "philosophers.h"

// 40 bytes per fork
typedef struct s_sim_cfg
{
	t_params		params;
	atomic_long		time_now;
	atomic_uchar	state[FT_MAX_PHILO];
	atomic_long		last_meal[FT_MAX_PHILO];
	unsigned char	prev_state[FT_MAX_PHILO];
	pthread_mutex_t	mutex[FT_MAX_PHILO];
}	t_sim_cfg;

int		monitor_state(t_sim_cfg *cfg);

#endif
