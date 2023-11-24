/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 22:24:21 by micarrel          #+#    #+#             */
/*   Updated: 2023/11/15 22:24:21 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_philos_full(t_general *philo, int i)
{
	if (philo->philo[i].eat_count == philo->must_eat 
		&& philo->philo[i].is_full == 0)
	{
		philo->philo_full++;
		philo->philo[i].is_full = 1;
		if (philo->philo_full == philo->philos_nbr)
		{
			philo->is_dead = 1;
			pthread_mutex_unlock(&philo->print);
			return (1);
		}
	}
	return (0);
}

int	is_dead(t_general	*philo, int i)
{
	if (get_time() - philo->philo[i].last_eat > philo->die_time
		&& philo->philo[i].is_eating != 1 && philo->philo[i].last_eat != -1)
	{
		philo->is_dead = 1;
		pthread_mutex_lock(&philo->print);
		printf("%d %d died\n", get_time() - philo->day_time, philo->philo[i].id);
		pthread_mutex_unlock(&philo->print);
		pthread_mutex_unlock(&philo->philo[i].can_eat);
		pthread_mutex_unlock(&philo->philo[i].can_die);
		return (1);
	}
	return (0);
}

void	supervisor(void	*philo_ptr)
{
	t_general	*philo;
	int			i;

	philo = (t_general *)philo_ptr;
	if (philo->philos_nbr == 1)
		return ;
	while (philo->is_dead == 0)
	{
		i = 0;
		while (i < philo->philos_nbr)
		{
			pthread_mutex_lock(&philo->philo[i].can_die);
			pthread_mutex_lock(&philo->philo[i].can_eat);
			if (is_dead(philo, i) == 1)
				break ;
			pthread_mutex_unlock(&philo->philo[i].can_eat);
			pthread_mutex_unlock(&philo->philo[i].can_die);
			pthread_mutex_lock(&philo->print);
			if (all_philos_full(philo, i) == 1)
				break ;
			pthread_mutex_unlock(&philo->print);
			i++;
		}
	}
}
