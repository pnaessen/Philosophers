/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 22:18:13 by pn                #+#    #+#             */
/*   Updated: 2025/04/03 16:44:10 by pnaessen         ###   ########lyon.fr   */
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
	take_both_forks(philo);
	if (should_stop(data))
	{
		release_both_forks(philo);
		return ;
	}
	print_status(philo, EATING);
	update_last_meal(philo);
	smart_sleep(data->time_to_eat, data);
	release_both_forks(philo);
}

void	handle_nietzsche(t_philo *philo)
{
	take_fork(philo, philo->left_fork);
	while (!should_stop(philo->data))
		usleep(100);
	release_fork(philo, philo->left_fork);
}
