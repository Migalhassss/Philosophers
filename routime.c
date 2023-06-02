/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:20:30 by micarrel          #+#    #+#             */
/*   Updated: 2023/05/28 17:20:30 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_general *general, int id, char c)
{
	pthread_mutex_lock(&(*general).print);
	if (c == 'e' && !(*general).is_dead)
		printf("%d ms %d is eating\n", get_time() - (*general).day_time,
			(*general).philo[id].id);
	else if (c == 'f' && !(*general).is_dead)
		printf("%d ms %d has taken a fork \n", get_time() - (*general).day_time,
			(*general).philo[id].id);
	else if (c == 't' && !(*general).is_dead)
		printf("%d ms %d is thinking\n", get_time() - (*general).day_time,
			(*general).philo[id].id);
	else if (c == 's' && !(*general).is_dead)
		printf("%d ms %d is sleeping\n", get_time() - (*general).day_time,
			(*general).philo[id].id);
	pthread_mutex_unlock(&(*general).print);
}

void	plswork(t_general *general, int id)
{
	if (philo_is_dead(general, id) == 0)
		return ;
	pthread_mutex_lock(&(*general).print);
	philo_take_fork(general, id);
	philo_eat(general, id);
	pthread_mutex_lock(&(*general).print);
	if (philo_is_dead(general, id) == 0)
		return ;
	philo_sleep(general, id);
	philo_think(general, id);
	pthread_mutex_lock(&(*general).print);
	usleep(100);
}

void	one_philo(t_general *general, int id)
{
	print_status(general, id, 'f');
	(*general).philo[id].last_eat = 0;
	usleep((*general).die_time * 1000);
	philo_is_dead(general, id);
}

void	*routime(void *arg)
{
	t_general	*general;
	int			id;

	general = (t_general *)arg;
	id = (*general).helper;
	if ((*general).philos_nbr == 1)
		one_philo(general, id);
	if ((*general).must_eat != -1)
	{	
		pthread_mutex_lock(&(*general).print);
		while ((*general).philo[id].eat_count < (*general).must_eat
			&& !(*general).is_dead)
			plswork(general, id);
		pthread_mutex_unlock(&(*general).print);
		return (NULL);
	}
	else
	{
		pthread_mutex_lock(&(*general).print);
		while (!(*general).is_dead)
			plswork(general, id);
		pthread_mutex_unlock(&(*general).print);
		return (NULL);
	}
	return (NULL);
}
