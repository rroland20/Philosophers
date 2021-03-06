/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:16:29 by rroland           #+#    #+#             */
/*   Updated: 2021/10/23 18:33:16 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_fork(t_all *all)
{
	int	i;

	i = 0;
	all->fork = malloc(sizeof(pthread_mutex_t) * all->P);
	if (!all->fork)
		return (1);
	while (i < all->P)
	{
		if (pthread_mutex_init(&all->fork[i], NULL))
			return (1);
		i++;
	}
	pthread_mutex_init(&all->dead, NULL);
	all->dead_flag = 1;
	pthread_mutex_init(&all->write, NULL);
	all->write_flag = 1;
	return (0);
}

int	init_philo(t_all *all, t_philo *philo)
{
	int	i;

	i = 0;
	all->time_flag = 0;
	while (i < all->P)
	{
		philo[i].all = all;
		philo[i].id = i + 1;
		philo[i].eat = 0;
		philo[i].num_of_eat = 0;
		philo[i].death = 0;
		if (i != 0)
			philo[i].l_fork = &(all->fork[i - 1]);
		else
			philo[i].l_fork = &(all->fork[all->P - 1]);
		philo[i].r_fork = &(all->fork[i]);
		i++;
	}
	return (0);
}

int	init_argc(int argc, char **argv, t_all *all, t_philo *philo)
{
	all->fork = NULL;
	all->dead_flag = 0;
	all->write_flag = 0;
	all->P = ft_atoi(argv[1]);
	all->to_die = ft_atoi(argv[2]) * 1000;
	all->to_eat = ft_atoi(argv[3]) * 1000;
	all->to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
	{
		all->num_of_times = ft_atoi(argv[5]);
		if (all->num_of_times == -1)
			return (1);
	}
	else
		all->num_of_times = -1;
	if (all->P < 1 || all->P > 200 || all->num_of_times < -1 || \
	all->to_die < 60000 || all->to_eat < 60000 || all->to_sleep < 60000)
		return (1);
	if (init_fork(all))
		return (1);
	if (init_philo(all, philo))
		return (1);
	return (0);
}
