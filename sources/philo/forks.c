/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:34:08 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/05 16:12:51 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

void	take_fork(void *mutex)
{
	pthread_mutex_lock(mutex);
}

void	drop_forks(void *mutex1, void *mutex2)
{
	pthread_mutex_unlock(mutex1);
	pthread_mutex_unlock(mutex2);
}
