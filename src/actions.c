/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 22:17:52 by pn                #+#    #+#             */
/*   Updated: 2025/02/10 16:10:30 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_philo *philo, t_status status)
{
	long	timestamp;
	char	*colors[5] = {GREEN, BLUE, YELLOW, CYAN, RED};
	char	*status_messages[5] = {"is eating", "is sleeping", "is thinking",
			"has taken a fork", "died"};

	pthread_mutex_lock(&philo->data->end_lock);
	sim_end = philo->data->simulation_end;
	pthread_mutex_unlock(&philo->data->end_lock);
	if (sim_end)
		return;
	pthread_mutex_lock(&philo->data->write_lock);
	if (!philo->data->simulation_end)
	{
		timestamp = get_current_time() - philo->data->start_time;
		printf("%s[%5ld ms] Philosopher %d %s %s\n", colors[status], timestamp,
			philo->id, status_messages[status], RESET);
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	take_forks(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->id % 2 != 0)
	{
		first_fork = philo->id - 1;
		second_fork = philo->id % philo->data->num_philos;
	}
	else
	{
		first_fork = philo->id % philo->data->num_philos;
		second_fork = philo->id - 1;
	}
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	print_status(philo, TAKING_FORK);
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	print_status(philo, TAKING_FORK);
}

void	release_forks(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->id % 2 != 0)
	{
		first_fork = philo->id - 1;
		second_fork = philo->id % philo->data->num_philos;
	}
	else
	{
		first_fork = philo->id % philo->data->num_philos;
		second_fork = philo->id - 1;
	}
	pthread_mutex_unlock(&philo->data->forks[second_fork]);
	pthread_mutex_unlock(&philo->data->forks[first_fork]);
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
// void	take_forks(t_philo *philo)
// {
// 	int	left;
// 	int	right;
// 	while (1)
// 	{

// 	}
// 	if (philo->id == 1)
// 	{
// 		left = philo->data->num_philos - 1;
// 		right = 0;
// 	}
// 	else
// 	{
// 		left = ((philo->id - 2) % philo->data->num_philos);
// 		right = ((philo->id - 1) % philo->data->num_philos);
// 	}
// 	pthread_mutex_lock(&philo->data->forks[left]);
// 	print_status(philo, TAKING_FORK);
// 	pthread_mutex_lock(&philo->data->forks[right]);
// 	print_status(philo, TAKING_FORK);
// }

// void	release_forks(t_philo *philo)
// {
// 	int	left;
// 	int	right;

// 	if (philo->id == 1)
// 	{
// 		left = philo->data->num_philos - 1;
// 		right = 0;
// 	}
// 	else
// 	{
// 		left = ((philo->id - 2) % philo->data->num_philos);
// 		right = ((philo->id - 1) % philo->data->num_philos);
// 	}
// 	pthread_mutex_unlock(&philo->data->forks[left]);
// 	pthread_mutex_unlock(&philo->data->forks[right]);
// }

// void	philo_eat(t_philo *philo)
// {
// 	take_forks(philo);
// 	print_status(philo, EATING);
// 	pthread_mutex_lock(&philo->data->meal_lock);
// 	philo->last_meal = get_current_time();
// 	philo->meals_eaten++;
// 	pthread_mutex_unlock(&philo->data->meal_lock);
// 	ft_sleep(philo->data->time_to_eat);
// 	release_forks(philo);
// }