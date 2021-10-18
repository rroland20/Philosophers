/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:12:54 by rroland           #+#    #+#             */
/*   Updated: 2021/10/18 17:52:55 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	give_time(struct timeval tv)
{
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	*thread(void *philo)
{
	int				i;
	struct timeval	tv;
	long			time;
	t_philo			*ph;

	i = 0;
	ph = (t_philo *)philo;
	if (gettimeofday(&tv, NULL))
		return ((void *)1);
	time = (tv.tv_sec * 1000000) + tv.tv_usec;
	// time = give_time(tv);
		pthread_mutex_lock(ph->l_fork);
		// pthread_mutex_lock(ph->r_fork);
		_usleep(ph->all->to_sleep);
		pthread_mutex_unlock(ph->l_fork);
		// pthread_mutex_unlock(ph->r_fork);
	printf("поток создан - %d\n", ph->id);
	return (0);
}

// void *mutex_die(void *philo)
// {
// 	t_philo	*ph;
// 	int		i;

// 	i = -1;
// 	ph = (t_philo *)philo;
// 	pthread_mutex_lock(&ph->all->dead);
// 	while (++i < ph->all->P)
// 		ph[i].death = 1;
// 	pthread_mutex_unlock(&ph->all->dead);
// 	return (0);
// }

int	start_thread(t_philo *philo, t_all *all)
{
	int i;

	i = 0;
	// pthread_mutex_lock(&all->dead);
	// pthread_create(&all->th, NULL, mutex_die, (void *)philo);
	while (i < all->P)
	{
		pthread_create(&philo[i].thread, NULL, thread, (void *)&(philo[i]));
		usleep(100000);
		i++;
	}
	i = -1;
	while (++i < all->P)
		if(pthread_join(philo[i].thread, NULL))
			return (1);
	return (0);
}

int main(int argc, char **argv)
{
	t_all		all;
	t_philo		*philo;

	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philo)
		return (print_error("error: memory allocation error"));
	if (argc != 5 && argc != 6)
		return (print_error("error: bad arguments"));
	if (init_argc(argc, argv, &all, philo))
		return (clear_all(&all, philo) && print_error("error: invalid arguments"));
	if (start_thread(philo, &all))
		return (clear_all(&all, philo) && print_error("error: thread creation error"));
	clear_all(&all, philo);
	return (0);
}











	// pthread_t	th;
	// void		*ret;
	// if (pthread_create(&th, NULL, thread, "thread 1"))
	// {
	// 	perror("pthread_create() error");
	// 	exit(1);
	// }

	// if (pthread_join(th, &ret) != 0) {
	// 	perror("pthread_create() error");
	// 	exit(3);
	// }