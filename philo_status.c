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

int	philo_is_dead(t_general *general, int id)
{
	if (get_time() - (*general).philo[id].last_eat >= (*general).die_time
		&& (*general).philo[id].last_eat != -1)
	{
		printf("%d %d died\n", get_time() - (*general).day_time,
			(*general).philo[id].id);
		(*general).is_dead = 1;
		pthread_mutex_unlock(&(*general).print);
		return (0);
	}
	pthread_mutex_unlock(&(*general).print);
	return (1);
}

void	philo_take_fork(t_general *general, int id)
{
	pthread_mutex_unlock(&(*general).print);
	pthread_mutex_lock((*general).philo[id].fork_left);
	print_status(general, id, 'f');
	pthread_mutex_lock((*general).philo[id].fork_right);
	print_status(general, id, 'f');
}

void	philo_eat(t_general *general, int id)
{
	pthread_mutex_lock(&(*general).philo[id].can_eat);
	(*general).philo[id].last_eat = get_time();
	(*general).philo[id].eat_count++;
	pthread_mutex_unlock(&(*general).philo[id].can_eat);
	print_status(general, id, 'e');
	usleep((*general).eat_time * 1015);
	pthread_mutex_unlock((*general).philo[id].fork_right);
	pthread_mutex_unlock((*general).philo[id].fork_left);
}

void	philo_sleep(t_general *general, int id)
{
	print_status(general, id, 's');
	usleep((*general).sleep_time * 1000);
}

void	philo_think(t_general *general, int id)
{
	print_status(general, id, 't');
}
