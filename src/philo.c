/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:28:13 by pn                #+#    #+#             */
/*   Updated: 2025/02/03 17:02:46 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;
	int		i;

	if (argc < 5 || argc > 6)
		return (printf("Usage:%s number time_die time_eat time_sleep [meals]\n", argv[0]), 1);
	if (init_data(&data, argc, argv) || init_philos(&data, &philos))
		return (1);
	i = -1;
	while (++i < data.num_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine,
				&philos[i]) != 0)
		{
			printf("Error: Failed to create philosopher thread %d\n", i);
			free(philos);
			free(data.forks);
			return (1);
		}
	}
	pthread_mutex_lock(&data.start_lock);
	data.start_flag = 1;
	pthread_mutex_unlock(&data.start_lock);
	if (pthread_create(&data.monitor_thread, NULL, monitor, philos) != 0)
	{
		printf("Error: Failed to create monitor thread\n");
		free(philos);
		free(data.forks);
		return (1);
	}
	i = -1;
	while (++i < data.num_philos)
		pthread_join(philos[i].thread, NULL);
	pthread_join(data.monitor_thread, NULL);
	pthread_mutex_destroy(&data.write_lock);
	pthread_mutex_destroy(&data.meal_lock);
	pthread_mutex_destroy(&data.end_lock);
	pthread_mutex_destroy(&data.start_lock);
	i = -1;
	while (++i < data.num_philos)
		pthread_mutex_destroy(&data.forks[i]);
	free(philos);
	free(data.forks);
	return (0);
}
