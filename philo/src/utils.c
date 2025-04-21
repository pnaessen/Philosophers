/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pn <pn@student.42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 22:18:43 by pn                #+#    #+#             */
/*   Updated: 2025/04/21 19:32:30 by pn               ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <limits.h>

int	ft_atoi(const char *str)
{
	long	res;
	int		sign;

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
		if (res > INT_MAX)
			return (-1);
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

void	free_allocated_resources(t_data *data, t_philo *philos, int mutex_count)
{
	int	i;
	int	fork_count;

	i = -1;
	if (data->forks)
	{
		fork_count = 0;
		if (mutex_count >= 6)
			fork_count = mutex_count - 6;
		else
			fork_count = 0;
		while (++i < fork_count)
			pthread_mutex_destroy(&data->forks[i].lock);
	}
	if (philos)
		free(philos);
	if (data->forks)
		free(data->forks);
}

void	cleanup_resources(t_data *data, t_philo *philos, bool exit,
		int mutex_count)
{
	if (mutex_count >= 1)
		pthread_mutex_destroy(&data->start_lock);
	if (mutex_count >= 2)
		pthread_mutex_destroy(&data->mutex_eat);
	if (mutex_count >= 3)
		pthread_mutex_destroy(&data->meal_lock);
	if (mutex_count >= 4)
		pthread_mutex_destroy(&data->write_lock);
	if (mutex_count >= 5)
		pthread_mutex_destroy(&data->meals_complete_lock);
	if (mutex_count >= 6)
		pthread_mutex_destroy(&data->end_lock);
	if (exit)
		free_allocated_resources(data, philos, mutex_count);
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
