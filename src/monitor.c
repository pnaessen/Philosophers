/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:57:42 by pn                #+#    #+#             */
/*   Updated: 2025/02/10 13:59:24 by pnaessen         ###   ########lyon.fr   */
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
			pthread_mutex_lock(&philos[i].data->write_lock); 
			print_status(&philos[i], DIED);
			pthread_mutex_unlock(&philos[i].data->write_lock);
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
			//pthread_mutex_lock(&philos->data->end_lock);
			set_simulation_end(philos->data);
			//pthread_mutex_inlock(&philos->data->end_lock);
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
	bool	complete;

	complete = false;
	if (data->max_meals > 0)
	{
		pthread_mutex_lock(&data->meals_complete_lock);
		complete = (data->meals_completed >= data->num_philos);
		pthread_mutex_unlock(&data->meals_complete_lock);
	}
	return (complete);
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