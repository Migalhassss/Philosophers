/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:45:20 by micarrel          #+#    #+#             */
/*   Updated: 2023/05/22 12:45:20 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <limits.h>

typedef struct s_philo
{
	int	id;
	int	last_eat;
	int	is_eating;
	int is_sleeping;
	int	is_thinking;
	int	is_dead;
	int	eat_count;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	can_eat;
}	t_philo;

typedef struct s_general
{
	int	helper;
	int	philos_nbr;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	must_eat;
	int	day_time;
	int	is_dead;
	int	philos_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*can_die;
	pthread_mutex_t	print;
	t_philo	*philo;
}	t_general;

/*-------------------------check_arguents.c------------------------*/

int		ft_isdigit(int i);
int		ftisdigit(char **argv);
int		ft_atoi(char *str);
int		valid_arguments(int ac, char **av);


/*__________________________________________________________________*/

/*------------------------------init.c-----------------------------*/

int		get_time(void);
int		check_numbers(t_general *philo);
void	start_threads(t_general *general);
int		init_arguments(t_general *philo, int ac, char **av);
void	init_philos(t_general *general);

/*__________________________________________________________________*/

/*-----------------------------routine.c---------------------------*/

void	*routime(void *arg);
void	philo_take_fork(t_general *general, int id);
void	philo_sleep(t_general *general, int id);
void	philo_think(t_general *general, int id);
void	philo_eat(t_general *general, int id);
int	philo_is_dead(t_general *general, int id);
void	print_status(t_general *general, int id, char c);

/*__________________________________________________________________*/
#endif