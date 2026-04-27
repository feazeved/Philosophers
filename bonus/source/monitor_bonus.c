/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:40:50 by feazeved          #+#    #+#             */
/*   Updated: 2026/04/27 19:46:50 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>
#include <unistd.h>

void    *monitor_routine(void *arg)
{
    t_philo *philo;
    int64_t elapsed;
 
    philo = (t_philo *)arg;
    while (1)
    {
        sem_wait(philo->table->meal_sem);
        elapsed = get_time_ms() - philo->last_meal_time;
        sem_post(philo->table->meal_sem);
        if (elapsed > philo->table->starve_time)
        {
            sem_wait(philo->table->print_sem);
            printf("%lld %d died\n", (long long)(get_time_ms() - philo->table->start_time), philo->id);
            sem_post(philo->table->death_sem);
            while (1)
                usleep(1000);
        }
        usleep(1000);
    }
    return (NULL);
}

