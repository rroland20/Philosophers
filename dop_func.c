/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:14:13 by rroland           #+#    #+#             */
/*   Updated: 2021/10/21 17:06:50 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	vsp(unsigned char *ss, int *k)
{
	int	i;

	i = 0;
	while (ss[i] == '\t' || ss[i] == '\n' || ss[i] == '\v'
		|| ss[i] == '\f' || ss[i] == '\r' || ss[i] == ' ')
		i++;
	if (ss[i] == '+')
		i++;
	else if (ss[i] == '-')
	{
		*k = -1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	unsigned char	*ss;
	int				res;
	int				i;
	int				k;
	int				r;

	res = 0;
	k = 1;
	r = 0;
	ss = (unsigned char *)str;
	i = vsp(ss, &k);
	while (ss[i] >= '0' && ss[i] <= '9')
	{
		res = res * 10 + (ss[i] - '0');
		i++;
		if (res != 0)
			r++;
	}
	if (ss[i] != 0)
		return (-1);
	return (res * k);
}

int	clear_all(t_philo *philo)
{
	int	i;

	i = -1;
	while (philo->all->fork && ++i < philo->all->P)
		pthread_mutex_destroy(philo->all->fork);
	if (philo->all->fork)
		free(philo->all->fork);
	pthread_mutex_destroy(&philo->all->dead);
	pthread_mutex_destroy(&philo->all->write);
	if (philo)
		free(philo);
	return (1);
}

int	print_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

void	_usleep(long time)
{
	struct timeval	begin;
	struct timeval	current;
	long			start;
	long			now;

	gettimeofday(&begin, NULL);
	gettimeofday(&current, NULL);
	start = (begin.tv_sec * 1000000) + begin.tv_usec;
	now = (current.tv_sec * 1000000) + current.tv_usec;
	while ((now - start) < time)
	{
		usleep(100);
		gettimeofday(&current, NULL);
		now = (current.tv_sec * 1000000) + current.tv_usec;
	}
}
