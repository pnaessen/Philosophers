/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 22:17:52 by pn                #+#    #+#             */
/*   Updated: 2025/02/13 10:45:16 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_philo *philo, t_status status)
{
	long	timestamp;
	char	*colors[5] = {GREEN, BLUE, YELLOW, CYAN, RED};
	char	*status_messages[5] = {"is eating", "is sleeping", "is thinking",
			"has taken a fork", "died"};
	bool	sim_end;

	pthread_mutex_lock(&philo->data->end_lock);
	sim_end = philo->data->simulation_end;
	pthread_mutex_unlock(&philo->data->end_lock);
	if (sim_end)
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	if (!philo->data->simulation_end)
	{
		timestamp = get_current_time() - philo->data->start_time;
		printf("%s[%5ld ms] Philosopher %d %s %s\n", colors[status], timestamp,
			philo->id, status_messages[status], RESET);
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	increment_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->meals_eaten++;
	if (philo->data->max_meals > 0
		&& philo->meals_eaten == philo->data->max_meals)
	{
		pthread_mutex_lock(&philo->data->meals_complete_lock);
		philo->data->meals_completed++;
		pthread_mutex_unlock(&philo->data->meals_complete_lock);
	}
	pthread_mutex_unlock(&philo->data->meal_lock);
}
