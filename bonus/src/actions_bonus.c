/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:36:16 by pnaessen          #+#    #+#             */
/*   Updated: 2025/04/01 14:00:50 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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
	sem_wait(philo->data->write);
	timestamp = get_current_time() - philo->data->start_time;
	printf("%s[%5ld ms] Philosopher %d %s %s\n", colors[status], timestamp,
		philo->id, status_messages[status], RESET);
	if (status != DIED)
		sem_post(philo->data->write);
}

void	update_last_meal(t_philo *philo)
{
	sem_wait(philo->data->meal_lock);
	philo->last_meal = get_current_time();
	sem_post(philo->data->meal_lock);
}
