/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:21:18 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/07 11:53:10 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdint.h>
# include <stddef.h>
# include <stdatomic.h>
# include <pthread.h>
# include <unistd.h>
# include <semaphore.h>
# include "philosophers.h"

typedef struct s_thread_cfg
{
	size_t			index;
	t_params		params;
	atomic_long		time_now;
	atomic_long		last_meal;
	atomic_uchar	state;
}	t_thread_cfg;

int		philo_start(size_t index, t_params params, const char *sem_name);
void	*monitor_start(void *varg);
void	philo_extinction(pid_t *cpid_list, size_t count);
void	philo_wait(pid_t *cpid_list, size_t count);

#endif
