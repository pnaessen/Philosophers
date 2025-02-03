/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 22:18:43 by pn                #+#    #+#             */
/*   Updated: 2025/02/03 13:59:02 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// void	ft_sleep(int ms)
// {
// 	long	start;
// 	long	elapsed;
// 	long	remaining;

// 	start = get_current_time();
// 	while (1)
// 	{
// 		elapsed = get_current_time() - start;
// 		if (elapsed >= ms)
// 			break ;
// 		remaining = ms - elapsed;
// 		if (remaining > 1)
// 			usleep(remaining * 1000);
// 		else
// 			usleep(1);
// 	}
// }

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
	pthread_mutex_lock(&data->meal_lock);
	while (++i < data->num_philos)
	{
		if (philos[i].meals_eaten < data->max_meals)
		{
			pthread_mutex_unlock(&data->meal_lock);
			return (false);
		}
	}
	pthread_mutex_unlock(&data->meal_lock);
	// pthread_mutex_lock(&data->write_lock);
	data->simulation_end = true;
	// pthread_mutex_unlock(&data->write_lock);
	return (true);
}

void	ft_sleep(int ms)
{
	long long	start;

	start = get_current_time();
	while (get_current_time() - start < ms)
		usleep(10);
}
