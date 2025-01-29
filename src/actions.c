/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pn <pn@student.42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 22:17:52 by pn                #+#    #+#             */
/*   Updated: 2025/01/29 22:17:56 by pn               ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_philo *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->write_lock);
	timestamp = get_current_time() - philo->data->start_time;
	if (!philo->data->simulation_end)
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	take_forks(t_philo *philo)
{
	int	fork1;
	int	fork2;

	fork1 = (philo->id - 1) % philo->data->num_philos;
	fork2 = philo->id % philo->data->num_philos;
	if (fork1 > fork2)
	{
		int	temp = fork1;
		fork1 = fork2;
		fork2 = temp;
	}
	pthread_mutex_lock(&philo->data->forks[fork1]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[fork2]);
	print_status(philo, "has taken a fork");
}

void	release_forks(t_philo *philo)
{
	int	fork1;
	int	fork2;

	fork1 = (philo->id - 1) % philo->data->num_philos;
	fork2 = philo->id % philo->data->num_philos;
	pthread_mutex_unlock(&philo->data->forks[fork1]);
	pthread_mutex_unlock(&philo->data->forks[fork2]);
}

void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	ft_sleep(philo->data->time_to_eat);
	release_forks(philo);
}
