/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:54:17 by feazeved          #+#    #+#             */
/*   Updated: 2026/03/11 17:54:59 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define FT_USAGE "Error: Usage: ./philo <number_of_philosophers> <time_to_die> \\
<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"

typedef struct	s_table
{
	int	number_philos;
	int	eat_time;
	int	die_time;
	int	sleep_time;
	int	number_meals;
}	t_table;

#endif