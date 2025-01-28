/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pn <pn@student.42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:28:13 by pn                #+#    #+#             */
/*   Updated: 2025/01/28 22:00:44 by pn               ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;
    int i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat "
			"time_to_sleep [max_meals]\n", argv[0]);
		return (1);
	}
	if (init_data(&data, argc, argv) || init_philos(&data, &philos))
		return (1);
    i = 0;
	while (i < data.num_philos)
	{
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}
	pthread_t	monitor_thread;
	pthread_create(&monitor_thread, NULL, monitor, philos);
    i = 0;
    while (i < data.num_philos)
    {
        pthread_join(philos[i].thread, NULL);
        i++;
    }
	free(philos);
	free(data.forks);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		print_status(philo, "is thinking");
		philo_eat(philo);
		philo_sleep_think(philo);
	}
	return (NULL);
}