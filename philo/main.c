/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:12:54 by rroland           #+#    #+#             */
/*   Updated: 2021/10/12 19:29:59 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clear_all(t_all *all, t_philo *philo)
{
	free(philo);
	return (1);
}

int	print_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

void	*thread(void *philo)
{
	int i;
	t_philo *ph;

	i = 1;
	ph = (t_philo *)philo;
	printf("поток создан\n");
	while (i <= ph->all->P)
	{
		pthread_mutex_lock(&ph->all->fork[i]);
		usleep(ph->all->to_sleep);
		pthread_mutex_unlock(&ph->all->fork[i]);
		i++;
	}
	return (0);
}

int	start_thread(t_philo *philo, t_all *all)
{
	int i;

	i = 0;
	while (i < all->P)
	{
		pthread_create(&philo[i].thread, NULL, thread, (void *)philo);
		pthread_detach(philo[i].thread);
		usleep(1000000);
		i++;
	}
	return (0);
}
	// all = malloc(sizeof(t_all));
	// if (!all)
	// 	return (print_error("error: memory allocation error"));


// кол.философов, вр до смерти, вр на еду, вр на сон, ск раз надо поесть каждому
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