/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:35:09 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/05 16:12:49 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>

void	take_fork(void *sem)
{
	sem_wait(sem);
}

void	drop_forks(void *sem1, void *sem2)
{
	sem_post(sem1);
	sem_post(sem2);
}
