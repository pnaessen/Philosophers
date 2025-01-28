/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pn <pn@student.42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:34:29 by pn                #+#    #+#             */
/*   Updated: 2025/01/28 22:00:55 by pn               ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
    int i;
	data->num_philos = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->max_meals = -1;
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	data->start_time = get_current_time();
	data->simulation_end = false;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
    i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->end_lock, NULL);
	return (0);
}

int	init_philos(t_data *data, t_philo **philos)
{
    int	i;
	*philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!*philos)
		return (1);
    i = 0;
    while (i < data->num_philos)
    {
        (*philos)[i].id = i + 1;
        (*philos)[i].last_meal = get_current_time();
        (*philos)[i].meals_eaten = 0;
        (*philos)[i].data = data;
        i++;
    }
	return (0);
}

