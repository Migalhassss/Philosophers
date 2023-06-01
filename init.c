/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:10:12 by micarrel          #+#    #+#             */
/*   Updated: 2023/05/28 17:10:12 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	check_numbers(t_general *philo)
{
	if ((*philo).philos_nbr < 1 || (*philo).philos_nbr > 200
		|| (*philo).die_time < 60)
		return (0);
	else if ((*philo).eat_time < 60 || (*philo).sleep_time < 60
		|| (*philo).must_eat == 0)
		return (0);
	return (1);
}

void	start_threads(t_general *general)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * (*general).philos_nbr);
	(*general).day_time = get_time();
	while (i < (*general).philos_nbr)
	{
		(*general).helper = i;
		pthread_create(&threads[i], NULL, &routime, general);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < (*general).philos_nbr)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	if ((*general).must_eat != -1)
		printf("All philosophers have eaten %d times\n", (*general).must_eat);
	free(threads);
}

int	init_arguments(t_general *general, int ac, char **av)
{
	int	i;

	i = 0;
	(*general).philos_nbr = ft_atoi(av[1]);
	(*general).die_time = ft_atoi(av[2]);
	(*general).eat_time = ft_atoi(av[3]);
	(*general).sleep_time = ft_atoi(av[4]);
	(*general).is_dead = 0;
	if (ac == 6)
		(*general).must_eat = ft_atoi(av[5]);
	else
		(*general).must_eat = -1;
	if (check_numbers(general) == 0)
		return (0);
	(*general).forks = malloc(sizeof(pthread_mutex_t) * (*general).philos_nbr);
	while (i < (*general).philos_nbr)
		pthread_mutex_init(&(*general).forks[i++], NULL);
	return (1);
}

void	init_philos(t_general *general)
{
	int	i;

	i = 0;
	(*general).philo = malloc(sizeof(t_philo) * (*general).philos_nbr);
	while (i < (*general).philos_nbr)
	{
		(*general).philo[i].id = i + 1;
		(*general).philo[i].fork_left = &(*general).forks[i];
		(*general).philo[i].fork_right = &(*general).forks[(i + 1)
			% (*general).philos_nbr];
		(*general).philo[i].eat_count = 0;
		(*general).philo[i].last_eat = -1;
		(*general).philo[i].is_eating = 0;
		(*general).philo[i].is_sleeping = 0;
		(*general).philo[i].is_thinking = 0;
		pthread_mutex_init(&(*general).philo[i].can_eat, NULL);
		pthread_mutex_init(&(*general).print, NULL);
		i++;
	}
}
