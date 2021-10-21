/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:54:32 by rroland           #+#    #+#             */
/*   Updated: 2021/10/21 17:08:33 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep_think(t_philo *philo)
{
	print_status(philo->eat, philo, "is sleeping");
	_usleep(philo->all->to_sleep);
	print_status(philo->eat, philo, "is thinking");
}

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_status(philo->eat, philo, "has taken a right fork");
	pthread_mutex_lock(philo->l_fork);
	print_status(philo->eat, philo, "has taken a left fork");
	gettimeofday(&philo->eat_end, NULL);
	print_status(philo->eat, philo, "is eating");
	_usleep(philo->all->to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*check_times_of_eat(void *ph)
{
	int				i;
	t_philo			*philo;

	i = 0;
	philo = (t_philo *)ph;
	while (i < philo->all->P)
	{
		if (philo[i].num_of_eat >= philo->all->num_of_times)
			i++;
		else
			_usleep(200);
	}
	if (philo->death != 1)
		print_status(philo->eat, philo, 0);
	return (NULL);
}

void	*thread(void *philo)
{
	t_philo			*ph;
	pthread_t		check;

	ph = (t_philo *)philo;
	gettimeofday(&ph->eat_end, NULL);
	ph->eat = give_time(ph->all->start_time);
	pthread_create(&check, NULL, check_time, philo);
	if (ph->id % 2 == 0)
		_usleep(ph->all->to_eat);
	else if (ph->all->P % 2 != 0 && ph->all->P == ph->id && ph->id != 1)
		_usleep(ph->all->to_eat + ph->all->to_sleep / 2);
	while (ph->death == 0)
	{
		philo_eating(ph);
		ph->num_of_eat++;
		philo_sleep_think(ph);
	}
	return (NULL);
}
