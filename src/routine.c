/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pn <pn@student.42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 22:18:13 by pn                #+#    #+#             */
/*   Updated: 2025/02/03 22:03:35 by pn               ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->start_lock);
	while (philo->data->start_flag == 0)
	{
		pthread_mutex_unlock(&philo->data->start_lock);
		usleep(100);
		pthread_mutex_lock(&philo->data->start_lock);
	}
	pthread_mutex_unlock(&philo->data->start_lock);
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		if (philo->data->simulation_end)
			break ;
		philo_eat(philo);
		print_status(philo, SLEEPING);
		ft_sleep(philo->data->time_to_sleep);
		print_status(philo, THINKING);
		if (philo->data->simulation_end)
			break ;
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
			if (get_current_time()
				- philos[i].last_meal > philos->data->time_to_die)
			{
				pthread_mutex_lock(&philos->data->write_lock);
				print_status(&philos[i], DIED);
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

	// if (philo->id == philo->data->num_philos)
	//   usleep(philo->data->time_to_eat * 1000);

// 	void *monitor(void *arg)
// {
// 	t_philo *philos = (t_philo *)arg;
// 	int i;
// 	long current_time;
// 	long last_meal_time;
// 	while (1)
// 	{
// 		i = -1;
// 		while (++i < philos->data->num_philos)
// 		{
// 			pthread_mutex_lock(&philos->data->meal_lock);
// 			current_time = get_current_time();
// 			last_meal_time = philos[i].last_meal;
// 			pthread_mutex_unlock(&philos->data->meal_lock);
// 			if (current_time - last_meal_time > philos->data->time_to_die)
// 			{
// 				pthread_mutex_lock(&philos->data->end_lock);
// 				if (!philos->data->simulation_end)
// 				{
// 					pthread_mutex_lock(&philos->data->write_lock);
// 					print_status(&philos[i], DIED);
// 					philos->data->simulation_end = true;
// 					pthread_mutex_unlock(&philos->data->write_lock);
// 				}
// 				pthread_mutex_unlock(&philos->data->end_lock);
// 				return NULL;
// 			}
// 		}
// 		if (check_meals_complete(philos->data, philos))
// 			break ;
// 		usleep(philos->data->time_to_die / 10);
// 	}
// 	return NULL;
// }