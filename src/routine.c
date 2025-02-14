/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 22:18:13 by pn                #+#    #+#             */
/*   Updated: 2025/02/14 13:45:35 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_for_start(t_philo *philo)
{
	bool	start;
	bool	end;

	while (true)
	{
		pthread_mutex_lock(&philo->data->start_lock);
		start = philo->data->start_flag;
		pthread_mutex_unlock(&philo->data->start_lock);
		if (start)
			break ;
		pthread_mutex_lock(&philo->data->end_lock);
		end = philo->data->simulation_end;
		pthread_mutex_unlock(&philo->data->end_lock);
		if (end)
			return ;
		usleep(100);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	update_last_meal(philo);
	wait_for_start(philo);
	if (philo->data->num_philos == 1)
	{
		handle_nietzsche(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(500);
	while (!should_stop(philo->data))
	{
		eat_routine(philo);
		increment_meals(philo);
		if (should_stop(philo->data))
			break ;
		sleep_and_think(philo);
		if (philo->data->max_meals > 0
			&& philo->meals_eaten >= philo->data->max_meals)
			break ;
		usleep(100);
	}
	return (NULL);
}

void	eat_routine(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		print_status(philo, TAKING_FORK);
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		print_status(philo, TAKING_FORK);
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		print_status(philo, TAKING_FORK);
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		print_status(philo, TAKING_FORK);
	}
	print_status(philo, EATING);
	update_last_meal(philo);
	smart_sleep(data->time_to_eat, data);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
}

void	handle_nietzsche(t_philo *philo)
{
	print_status(philo, TAKING_FORK);
	while (!should_stop(philo->data))
		usleep(100);
}