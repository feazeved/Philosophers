/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:04:26 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/07 10:30:51 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdint.h>
#include <stddef.h>
#include "philosophers.h"

// Returns: 0) OK, -1) ARGCOUNT
static
int	stt_init_multiple(const char **argv, size_t count, t_params *params)
{
	size_t		i;
	const char	*str;
	int64_t		vars[5];

	i = 0;
	vars[4] = LONG_MAX;
	while (i < count)
	{
		str = argv[i];
		while (*str == ' ' || (*str >= 9 && *str <= 14))
			str++;
		if (!(*str >= '0' && *str <= '9'))
			return (-1);
		vars[i] = ft_strtol(str);
		if (vars[i] < 0)
			return (-1);
		i++;
	}
	params->count = (size_t) vars[0];
	params->death = FT_MS * (vars[1]) + FT_LAG_COMPENSATION;
	params->eat = FT_MS * (vars[2]);
	params->sleep = FT_MS * (vars[3]);
	params->eat_count = vars[4];
	return (0);
}

// num_ph, die, eat, sleep, eat_count
// Returns: 0) OK, -1) ARGCOUNT
static
int	stt_init_single(const char *str, t_params *philos)
{
	size_t	i;
	int64_t	vars[5];

	i = 0;
	vars[4] = LONG_MAX;
	while (i < 5 && *str >= '0' && *str <= '9')
	{
		vars[i] = ft_strtol(str);
		if (vars[i] < 0)
			return (-1);
		while (*str >= '0' && *str <= '9')
			str++;
		while (*str == ' ' || (*str >= 9 && *str <= 14))
			str++;
		i++;
	}
	if (*str != 0 || i < 4)
		return (-1);
	philos->count = (size_t) vars[0];
	philos->death = FT_MS * vars[1] + FT_LAG_COMPENSATION;
	philos->eat = FT_MS * vars[2];
	philos->sleep = FT_MS * vars[3];
	philos->eat_count = vars[4];
	return (0);
}

// Returns: 0) OK, -1) ARGCOUNT, -2) EINVAL, -4) Philos outside range
int	init_params(int argc, const char **argv, t_params *philos)
{
	int	rvalue;

	if (argc != 2 && argc != 5 && argc != 6)
	{
		write(STDERR_FILENO, "init_error: invalid argument count\n", 35);
		return (-1);
	}
	if (argc == 2)
		rvalue = stt_init_single(argv[1], philos);
	else
		rvalue = stt_init_multiple(argv + 1, (size_t)(argc - 1), philos);
	if (rvalue == -1)
	{
		write(STDERR_FILENO, "init_error: argument is not a number\n", 37);
		return (-2);
	}
	if (philos->count == 0 || philos->count > FT_MAX_PHILO)
	{
		write(STDERR_FILENO, "init_error: invalid philo count\n", 32);
		return (-4);
	}
	return (0);
}
