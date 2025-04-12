/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 22:18:43 by pn                #+#    #+#             */
/*   Updated: 2025/04/12 12:46:19 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->data->meal_lock);
}

void	cleanup_resources(t_data *data, t_philo *philos, bool exit)
{
	int	i;

	i = -1;
	if (data->forks)
	{
		while (++i < data->num_philos)
			pthread_mutex_destroy(&data->forks[i].lock);
	}
	pthread_mutex_destroy(&data->start_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meals_complete_lock);
	pthread_mutex_destroy(&data->mutex_eat);
	pthread_mutex_destroy(&data->end_lock);
	if (exit)
	{
		if (philos)
			free(philos);
		free(data->forks);
	}
}

bool	should_stop(t_data *data)
{
	bool	stop;

	pthread_mutex_lock(&data->end_lock);
	stop = data->simulation_end;
	pthread_mutex_unlock(&data->end_lock);
	return (stop);
}

bool	check_all_meals_complete(t_data *data)
{
	bool	max_meal;

	max_meal = false;
	if (data->max_meals > 0)
	{
		pthread_mutex_lock(&data->meals_complete_lock);
		max_meal = (data->meals_completed >= data->num_philos);
		pthread_mutex_unlock(&data->meals_complete_lock);
	}
	return (max_meal);
}
