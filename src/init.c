/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:34:29 by pn                #+#    #+#             */
/*   Updated: 2025/02/05 10:40:24 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->max_meals = -1;
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	data->start_time = get_current_time();
	data->simulation_end = false;
	data->threads_ready = 0;
	data->start_flag = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks || data->num_philos <= 0 || (argc == 6 && data->max_meals <= 0))
		return (1);
	pthread_mutex_init(&data->start_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->end_lock, NULL);
	pthread_mutex_init(&data->meals_complete_lock, NULL);
	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	return (0);
}

int	init_philos(t_data *data, t_philo **philos)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!*philos)
		return (1);
	i = -1;
	while (++i < data->num_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].last_meal = data->start_time;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].data = data;
	}
	return (0);
}
