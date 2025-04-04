/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:05:20 by pn                #+#    #+#             */
/*   Updated: 2025/04/04 17:13:58 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	take_fork(t_philo *philo, int fork_id)
{
	bool	success;

	success = false;
	pthread_mutex_lock(&philo->data->forks[fork_id].lock);
	if (!philo->data->forks[fork_id].is_taken)
	{
		philo->data->forks[fork_id].is_taken = true;
		success = true;
		print_status(philo, TAKING_FORK);
	}
	pthread_mutex_unlock(&philo->data->forks[fork_id].lock);
	return (success);
}

void	release_fork(t_philo *philo, int fork_id)
{
	pthread_mutex_lock(&philo->data->forks[fork_id].lock);
	philo->data->forks[fork_id].is_taken = false;
	pthread_mutex_unlock(&philo->data->forks[fork_id].lock);
}

void	select_forks(t_philo *philo, int *first, int *second)
{
	if (philo->id % 2 != 0)
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
	else
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
}

void	take_both_forks(t_philo *philo)
{
	bool	use_mutex;
	t_data	*data;
	int		first_fork;
	int		second_fork;

	data = philo->data;
	use_mutex = (data->num_philos <= 171
			&& data->time_to_sleep < data->time_to_eat && data->num_philos
			% 2 != 0);
	select_forks(philo, &first_fork, &second_fork);
	if (use_mutex)
		pthread_mutex_lock(&data->mutex_eat);
	while (!should_stop(data) && !take_fork(philo, first_fork))
		usleep(100);
	if (use_mutex)
		pthread_mutex_unlock(&data->mutex_eat);
	if (should_stop(data))
	{
		release_fork(philo, first_fork);
		return ;
	}
	while (!should_stop(data) && !take_fork(philo, second_fork))
		usleep(100);
	if (should_stop(data))
		release_both_forks(philo);
}

void	release_both_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		release_fork(philo, philo->right_fork);
		release_fork(philo, philo->left_fork);
	}
	else
	{
		release_fork(philo, philo->left_fork);
		release_fork(philo, philo->right_fork);
	}
}
