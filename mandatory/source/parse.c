/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:54:17 by feazeved          #+#    #+#             */
/*   Updated: 2026/03/11 17:54:59 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include "philo.h"

// Function that will translate the args into int32_t for t_table
//
// Error value: -1) Invalid argument,  -2) Empty arg  -3) int overflow
static long	stt_philo_strtol(char *str, int *error)
{
	int64_t	n;

	n = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*error = -1;
		str++;
	}
	if (!*str)
		*error = -2;
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + (*str++ - '0');
		if (n > INT_MAX)
			*error = -3;
	}
	if (*str)
		*error = -1;
	return (n);
}

//   Function responsible to check argc and call the function that will parse
// the args.
//
//   Return value: 0) Success,  1) Error on parsing
int	parse_args(t_table *table, int argc, char **argv)
{
	int	error;

	if (argc < 5 || argc > 6)
	{
		write(STDERR_FILENO, FT_USAGE, 56);
		return (1);
	}
	error = 0;
	table->number_philos = stt_philo_strtol(argv[1], &error);
	table->starve_time = stt_philo_strtol(argv[2], &error);
	table->eat_time = stt_philo_strtol(argv[3], &error);
	table->sleep_time = stt_philo_strtol(argv[4], &error);
	table->number_meals = -1;
	if (argc == 6)
		table->number_meals = stt_philo_strtol(argv[5], &error);
	if (error)
	{
		write(STDERR_FILENO, FT_INVALID_ARG, 47);
		return (1);
	}
	return (0);
}
