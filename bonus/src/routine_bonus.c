/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:35:24 by pnaessen          #+#    #+#             */
/*   Updated: 2025/04/02 13:27:12 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_status(philo, TAKING_FORK);
	sem_wait(philo->data->forks);
	print_status(philo, TAKING_FORK);
}

void	eat_routine(t_philo *philo)
{
	take_forks(philo);
	print_status(philo, EATING);
	update_last_meal(philo);
	smart_sleep(philo->data->time_to_eat);
	philo->meals_eaten++;
	if (philo->data->max_meals > 0
		&& philo->meals_eaten >= philo->data->max_meals)
		sem_post(philo->data->finished);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	sleep_and_think(t_philo *philo)
{
	print_status(philo, SLEEPING);
	smart_sleep(philo->data->time_to_sleep);
	print_status(philo, THINKING);
}

void	philo_routine(t_philo *philo)
{
	pthread_create(&philo->monitor_thread, NULL, monitor_routine, philo);
	//pthread_detach(philo->monitor_thread); //bug
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		eat_routine(philo);
		sleep_and_think(philo);
	}
}
