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

// Return value: -1) Negative number,  -2) Empty arg  -3) int oveerlow
// -3
static long	stt_philo_strtol(char *str)
{
	long	n;

	n = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (-1);
		str++;
	}
	if (!*str)
		return (-2);
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + (*str++ - '0');
		if (n < INT_MIN || n > INT_MAX)
			return (-3);
	}
	return (n);
}

int	parse(t_table *table, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (write(STDERR_FILENO, FT_USAGE, 137), 1);
	
	
	
}
