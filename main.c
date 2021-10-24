/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:12:54 by rroland           #+#    #+#             */
/*   Updated: 2021/10/24 20:16:07 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	give_time(struct timeval tv)
{
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_status(long start, t_philo *ph, char *status)
{
	struct timeval	tv;

	pthread_mutex_lock(&ph->all->write);
	if (ph->death != 1)
	{
		gettimeofday(&tv, NULL);
		if (status != 0)
			printf("%ld %d %s\n", give_time(tv) - start, ph->id, status);
		else
		{
			pthread_mutex_unlock(&ph->all->dead);
			printf("All the philosophers have eaten %d times\n", \
				ph->all->num_of_times);
			usleep(100 * ph->all->P);
		}
	}
	pthread_mutex_unlock(&ph->all->write);
}

int	start_thread(t_philo *philo, t_all *all)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&all->dead);
	if (all->num_of_times > 0)
		pthread_create(&all->th, NULL, check_times_of_eat, (void *)philo);
	pthread_create(&all->th, NULL, mutex_die, (void *)philo);
	gettimeofday(&all->start_time, NULL);
	while (++i < all->P)
		pthread_create(&philo[i].thread, NULL, thread, (void *)&(philo[i]));
	i = -1;
	while (++i < all->P)
		if (pthread_join(philo[i].thread, NULL))
			return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_all		all;
	t_philo		*philo;

	if ((argc != 5 && argc != 6) || ft_atoi(argv[1]) < 1)
		return (print_error("error: bad arguments"));
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	philo->all = &all;
	if (!philo)
		return (print_error("error: memory allocation error"));
	if (init_argc(argc, argv, &all, philo))
		return (clear_all(philo) && \
			print_error("error: invalid arguments"));
	if (start_thread(philo, &all))
		return (clear_all(philo) && \
			print_error("error: thread creation error"));
	clear_all(philo);
	return (0);
}
