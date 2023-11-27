/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:45:18 by micarrel          #+#    #+#             */
/*   Updated: 2023/05/22 12:45:18 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_general *general)
{
	free(general->philo);
	free(general->forks);
}

void	destroy_mutex(t_general *general)
{
	int	i;

	i = 0;
	while (i > general->philos_nbr)
	{
		pthread_mutex_destroy(&general->philo[i].can_die);
		pthread_mutex_destroy(&general->forks[i]);
		pthread_mutex_destroy(&general->helper_mutex);
		pthread_mutex_destroy(&general->print);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_general	general;

	if (valid_arguments(ac, av))
	{
		if (init_arguments(&general, ac, av) == 0)
			return (printf("Error Arguments\nEx: ./philo 1 60 60 60 '1'\n"));
		init_philos(&general);
		start_threads(&general);
		destroy_mutex(&general);
		free_all(&general);
	}
	else
		printf("Error Arguments\nEx: ./philo 1 60 60 60 '1'\n");
}
