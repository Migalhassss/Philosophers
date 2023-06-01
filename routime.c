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
	if (c == 'e')
		printf("%d ms %d is eating\n", get_time() - (*general).day_time,
			(*general).philo[id].id);
	else if (c == 'f')
		printf("%d ms %d has taken a fork \n", get_time() - (*general).day_time,
			(*general).philo[id].id);
	else if (c == 't')
		printf("%d ms %d is thinking\n", get_time() - (*general).day_time,
			(*general).philo[id].id);
	else if (c == 's')
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

void	*routime(void *arg)
{
	t_general	*general;
	int			id;

	general = (t_general *)arg;
	id = (*general).helper;
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
