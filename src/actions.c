/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 22:17:52 by pn                #+#    #+#             */
/*   Updated: 2025/02/18 11:05:27 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_messages(char *colors[5], char *status_messages[5])
{
	colors[0] = GREEN;
	colors[1] = BLUE;
	colors[2] = YELLOW;
	colors[3] = CYAN;
	colors[4] = RED;
	status_messages[0] = "is eating";
	status_messages[1] = "is sleeping";
	status_messages[2] = "is thinking";
	status_messages[3] = "has taken a fork";
	status_messages[4] = "died";
}

void	print_status(t_philo *philo, t_status status)
{
	long	timestamp;
	char	*colors[5];
	char	*status_messages[5];

	init_messages(colors, status_messages);
	if (should_stop(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	timestamp = get_current_time() - philo->data->start_time;
	printf("%s[%5ld ms] Philosopher %d %s %s\n", colors[status], timestamp,
		philo->id, status_messages[status], RESET);
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
