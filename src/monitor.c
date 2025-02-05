/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:57:42 by pn                #+#    #+#             */
/*   Updated: 2025/02/05 11:56:08 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_philo_death(t_philo *philo)
{
	long	time_since_meal;
	bool	alive;

	pthread_mutex_lock(&philo->data->meal_lock);
	time_since_meal = get_current_time() - philo->last_meal;
	alive = (time_since_meal < philo->data->time_to_die);
	pthread_mutex_unlock(&philo->data->meal_lock);
	return (!alive);
}

bool	check_any_death(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->num_philos)
	{
		if (check_philo_death(&philos[i]))
		{
			print_status(&philos[i], DIED);
			return (true);
		}
		i++;
	}
	return (false);
}

void	*monitor(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (!should_stop(philos->data))
	{
		if (check_any_death(philos) || check_all_meals_complete(philos->data))
		{
			set_simulation_end(philos->data);
			break ;
		}
		usleep(500);
	}
	return (NULL);
}

void	set_simulation_end(t_data *data)
{
	pthread_mutex_lock(&data->end_lock);
	data->simulation_end = true;
	pthread_mutex_unlock(&data->end_lock);
}

// void	*monitor(void *arg)
// {
// 	t_philo	*philos;
// 	int		i;

// 	philos = (t_philo *)arg;
// 	while (1)
// 	{
// 		i = -1;
// 		while (++i < philos->data->num_philos)
// 		{
// 			pthread_mutex_lock(&philos->data->meal_lock);
// 			if (get_current_time()
// 				- philos[i].last_meal > philos->data->time_to_die)
// 			{
// 				pthread_mutex_lock(&philos->data->write_lock);
// 				print_status(&philos[i], DIED);
// 				philos->data->simulation_end = true;
// 				pthread_mutex_unlock(&philos->data->meal_lock);
// 				pthread_mutex_unlock(&philos->data->write_lock);
// 				return (NULL);
// 			}
// 			pthread_mutex_unlock(&philos->data->meal_lock);
// 		}
// 		if (check_meals_complete(philos->data, philos))
// 			break ;
// 		usleep(100);
// 	}
// 	return (NULL);
// }