/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pn <pn@student.42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:34:29 by pn                #+#    #+#             */
/*   Updated: 2025/04/21 19:33:04 by pn               ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->start_lock, NULL) != 0)
		return (cleanup_resources(data, NULL, true, 0), 1);
	if (pthread_mutex_init(&data->mutex_eat, NULL) != 0)
		return (cleanup_resources(data, NULL, true, 1), 1);
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		return (cleanup_resources(data, NULL, true, 2), 1);
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (cleanup_resources(data, NULL, true, 3), 1);
	if (pthread_mutex_init(&data->meals_complete_lock, NULL) != 0)
		return (cleanup_resources(data, NULL, true, 4), 1);
	if (pthread_mutex_init(&data->end_lock, NULL) != 0)
		return (cleanup_resources(data, NULL, true, 5), 1);
	i = -1;
	while (++i < data->num_philos)
	{
		data->forks[i].id = i;
		data->forks[i].is_taken = false;
		if (pthread_mutex_init(&data->forks[i].lock, NULL) != 0)
			return (cleanup_resources(data, NULL, true, 6 + i), 1);
	}
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	int	status;

	data->max_meals = -1;
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	data->threads_ready = 0;
	data->start_flag = 0;
	data->forks = malloc(sizeof(t_fork) * data->num_philos);
	if (!data->forks || data->num_philos <= 0 || (argc == 6
			&& data->max_meals <= 0))
	{
		if (data->forks)
			free(data->forks);
		return (1);
	}
	status = init_data_mutex(data);
	return (status);
}

int	init_philos(t_data *data, t_philo **philos)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!*philos)
	{
		cleanup_resources(data, *philos, true, 6);
		return (1);
	}
	i = -1;
	while (++i < data->num_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].last_meal = data->start_time;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].data = data;
		(*philos)[i].left_fork = i;
		(*philos)[i].right_fork = (i + 1) % data->num_philos;
	}
	return (0);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}
