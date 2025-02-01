/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pn <pn@student.42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 22:18:13 by pn                #+#    #+#             */
/*   Updated: 2025/02/01 22:38:53 by pn               ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->start_lock);
	philo->data->threads_ready++;
	pthread_mutex_unlock(&philo->data->start_lock);
	while (!philo->data->simulation_end)
	{
		philo_eat(philo);
		print_status(philo, "is sleeping");
		ft_sleep(philo->data->time_to_sleep);
		print_status(philo, "is thinking");
		pthread_mutex_lock(&philo->data->end_lock);
		if (philo->data->simulation_end)
		{
			pthread_mutex_unlock(&philo->data->end_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->end_lock);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	while (1)
	{
		i = -1;
		while (++i < philos->data->num_philos)
		{
			pthread_mutex_lock(&philos->data->meal_lock);
			if (get_current_time() - philos[i].last_meal > philos->data->time_to_die)
			{
				pthread_mutex_lock(&philos->data->write_lock);
				printf("%ld %d died\n",
					get_current_time() - philos->data->start_time, philos[i].id);
				philos->data->simulation_end = true;
				pthread_mutex_unlock(&philos->data->meal_lock);
				pthread_mutex_unlock(&philos->data->write_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&philos->data->meal_lock);
		}
		if (check_meals_complete(philos->data, philos))
			break ;
		usleep(100);
	}
	return (NULL);
}
