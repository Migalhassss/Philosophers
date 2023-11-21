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
			if (get_time() - philo->philo[i].last_eat > philo->die_time
				&& philo->philo[i].is_eating != 1)
			{
				philo->is_dead = 1;
				pthread_mutex_lock(&philo->print);
				printf("last eat %d\n", get_time() - philo->philo[i].last_eat);
				printf("%d %d died\n", get_time() - philo->day_time, philo->philo[i].id);
				pthread_mutex_unlock(&philo->print);
				pthread_mutex_unlock(&philo->philo[i].can_eat);
				pthread_mutex_unlock(&philo->philo[i].can_die);
				break ;
			}
			pthread_mutex_unlock(&philo->philo[i].can_eat);
			pthread_mutex_unlock(&philo->philo[i].can_die);
			pthread_mutex_lock(&philo->print);
			if (philo->philo[i].eat_count == philo->must_eat)
			{
				philo->philo_full++;
				if (philo->philo_full == philo->philos_nbr)
				{
					philo->is_dead = 1;
					pthread_mutex_unlock(&philo->print);
					break ;
				}	
			}
			pthread_mutex_unlock(&philo->print);
			i++;
		}
	}
}