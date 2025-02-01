/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pn <pn@student.42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 22:18:43 by pn                #+#    #+#             */
/*   Updated: 2025/02/01 19:52:32 by pn               ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void    ft_sleep(int ms)
{
    long    start;
    long    elapsed;

    start = get_current_time();
    while (1)
    {
        elapsed = get_current_time() - start;
        if (elapsed >= ms)
            break;
        if (ms - elapsed > 5)
            usleep(1000);
        else
            usleep(100);
    }
}

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

bool	check_meals_complete(t_data *data, t_philo *philos)
{
	int	i;

	if (data->max_meals == -1)
		return (false);
	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (philos[i].meals_eaten < data->max_meals)
		{
			pthread_mutex_unlock(&data->meal_lock);
			return (false);
		}
		pthread_mutex_unlock(&data->meal_lock);
	}
	pthread_mutex_lock(&data->write_lock);
	data->simulation_end = true;
	pthread_mutex_unlock(&data->write_lock);
	return (true);
}
