/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 11:52:03 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/07 11:58:18 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

void	philo_extinction(pid_t *cpid_list, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		kill(cpid_list[i], SIGKILL);
		i++;
	}
	i = 0;
	while (i < count)
	{
		waitpid(cpid_list[i], NULL, 0);
		i++;
	}
}

void	philo_wait(pid_t *cpid_list, size_t count)
{
	int		status;
	int		code;
	size_t	done_count;
	bool	dead;

	dead = false;
	done_count = 0;
	while (!dead && done_count < count)
	{
		if (waitpid(-1, &status, 0) < 0)
			break ;
		if (WIFEXITED(status))
		{
			code = WEXITSTATUS(status);
			if (code == 1)
				dead = true;
			else if (code == 0)
				done_count++;
		}
	}
	philo_extinction(cpid_list, count);
}
