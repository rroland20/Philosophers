/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:13:09 by rroland           #+#    #+#             */
/*   Updated: 2021/10/21 17:06:56 by rroland          ###   ########.fr       */
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

typedef struct s_all
{
	int				P;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				num_of_times;
	int				time_flag;
	pthread_t		th;
	pthread_mutex_t	*fork;
	pthread_mutex_t	dead;
	pthread_mutex_t	write;
	struct timeval	start_time;
}					t_all;

typedef struct s_philo
{
	int				id;
	long int		eat;
	int				death;
	int				num_of_eat;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct timeval	eat_end;
	t_all			*all;

}					t_philo;

int			ft_atoi(const char *str);
int			init_argc(int argc, char **argv, t_all *all, t_philo *philo);
int			init_philo(t_all *all, t_philo *philo);
int			init_fork(t_all *all);
int			clear_all(t_philo *philo);
int			print_error(char *str);
void		_usleep(long time);
void		philo_eating(t_philo *philo);
void		*thread(void *philo);
void		*check_time(void *philo);
void		*mutex_die(void *philo);
void		print_status(long start, t_philo *ph, char *status);
long int	give_time(struct timeval tv);
void		*check_times_of_eat(void *ph);

#endif