/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:13:09 by rroland           #+#    #+#             */
/*   Updated: 2021/10/14 13:34:57 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
// кол.философов, вр до смерти, вр на еду, вр на сон, ск раз надо поесть каждому

typedef struct s_all
{
	int				P;
	int	to_die;
	int	to_eat;
	int	to_sleep;
	int				num_of_times;
	pthread_mutex_t *fork;
}					t_all;

typedef struct s_philo
{
	int				id;
	int				eat;
	int				sleep;
	int				think;
	int				death;
	pthread_t		thread;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	t_all			*all;

}					t_philo;

int	ft_atoi(const char *str);
int	init_argc(int argc, char **argv, t_all *all, t_philo *philo);
int	init_philo(t_all *all, t_philo *philo);
int	init_fork(t_all *all);

#endif