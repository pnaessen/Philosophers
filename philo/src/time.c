/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:04:17 by pnaessen          #+#    #+#             */
/*   Updated: 2025/04/22 11:06:44 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_current_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

long	get_ms_since_start(t_data *data)
{
	long	time;

	time = get_current_time() - data->start_time;
	return (time);
}

void	smart_sleep(long duration, t_data *data)
{
	long	start;
	long	elapsed;

	start = get_current_time();
	while (!should_stop(data))
	{
		elapsed = get_current_time() - start;
		if (elapsed >= duration)
			break ;
		usleep(300);
	}
}

void	sleep_and_think(t_philo *philo)
{
	print_status(philo, SLEEPING);
	smart_sleep(philo->data->time_to_sleep, philo->data);
	print_status(philo, THINKING);
	usleep(500);
}

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->data->meal_lock);
}
