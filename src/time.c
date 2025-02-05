/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:04:17 by pnaessen          #+#    #+#             */
/*   Updated: 2025/02/05 16:18:33 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	get_ms_since_start(t_data *data)
{
	return (get_current_time() - data->start_time);
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
}
