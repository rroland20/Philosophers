/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:57:01 by rroland           #+#    #+#             */
/*   Updated: 2021/10/21 17:07:42 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_time1(t_philo *ph, int flag)
{
	struct timeval	tv;
	long			time;
	long			time1;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000000 + tv.tv_usec;
	time1 = ph->eat_end.tv_sec * 1000000 + ph->eat_end.tv_usec;
	if (time - time1 > ph->all->to_die)
	{
		pthread_mutex_unlock(&ph->all->dead);
		if (!flag)
		{
			print_status(ph->eat, ph, "is died");
			flag++;
		}
	}
	usleep(200);
}

void	*check_time(void *philo)
{
	t_philo			*ph;

	ph = (t_philo *)philo;
	while (ph->death == 0)
		check_time1(ph, 0);
	pthread_mutex_unlock(ph->l_fork);
	pthread_mutex_unlock(ph->r_fork);
	return (NULL);
}

void	*mutex_die(void *philo)
{
	t_philo	*ph;
	int		i;

	i = -1;
	ph = (t_philo *)philo;
	pthread_mutex_lock(&ph->all->dead);
	while (++i < ph->all->P)
	{
		ph[i].death = 1;
		ph[i].num_of_eat = ph->all->num_of_times;
	}
	pthread_mutex_unlock(&ph->all->dead);
	return (NULL);
}
