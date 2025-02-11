/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:54:20 by pnaessen          #+#    #+#             */
/*   Updated: 2025/02/11 11:07:48 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo philo_count t_die t_eat t_sleep [meals]\n");
		return (0);
	}
	return (1);
}

int	init_simu(t_data *data, int argc, char **argv, t_philo **philos)
{
	if (init_data(data, argc, argv) != 0 || init_philos(data, philos) != 0)
		return (1);
	data->start_time = get_current_time();
	return (0);
}

int	create_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]))
		{
			printf("Error: Thread creation failed\n");
			return (1);
		}
	}
	if (pthread_create(&data->monitor_thread, NULL, monitor, philos) != 0)
	{
		printf("Error: Monitor thread failed\n");
		return (1);
	}
	return (0);
}

void	start_simu(t_data *data)
{
	pthread_mutex_lock(&data->start_lock);
	data->start_flag = 1;
	pthread_mutex_unlock(&data->start_lock);
}

void	join_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
		pthread_join(philos[i].thread, NULL);
	pthread_join(data->monitor_thread, NULL);
}
