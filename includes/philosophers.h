/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:10:29 by adeimlin          #+#    #+#             */
/*   Updated: 2025/12/07 10:35:01 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdint.h>
# include <stddef.h>
# include <stdatomic.h>
# include <unistd.h>

# ifndef FT_MAX_PHILO
#  define FT_MAX_PHILO 512
# endif

# ifndef FT_LAG_COMPENSATION
#  define FT_LAG_COMPENSATION 0
# endif

// Make the simulation go faster
# ifndef FT_MS
#  define FT_MS 1000
# endif 

# ifndef FT_TICK_INTERVAL
#  define FT_TICK_INTERVAL 1
# endif

typedef struct s_params
{
	size_t	count;
	long	death;
	long	eat;
	long	sleep;
	long	eat_count;
}	t_params;

typedef struct s_philo
{
	size_t			index;
	t_params		params;
	atomic_long		*time_now;
	atomic_long		*last_meal;
	atomic_uchar	*state;
	void			*forks[2];
}	t_philo;

enum e_philo_state
{
	e_death = 0,
	e_idle = 1u,
	e_fork0 = 2u,
	e_fork1 = 3u,
	e_eat = 4u,
	e_sleep = 5u,
	e_done = 6u
};

int			init_params(int argc, const char **argv, t_params *philos);
int			philo_loop(t_philo *ph);
void		take_fork(void *ptr);
void		drop_forks(void *ptr1, void *ptr2);
int64_t		ft_strtol(const char *str);
char		*ft_itoa_r(int64_t number, char *ptr);
ssize_t		ft_writev(int fd, const char **vec, char endl);

#endif