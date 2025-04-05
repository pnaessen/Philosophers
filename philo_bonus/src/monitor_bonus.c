/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:40:32 by pnaessen          #+#    #+#             */
/*   Updated: 2025/04/05 11:42:46 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

bool	check_death(t_philo *philo)
{
	long	time_since_meal;
	bool	is_dead;

	sem_wait(philo->data->meal_lock);
	time_since_meal = get_current_time() - philo->last_meal;
	is_dead = (time_since_meal >= philo->data->time_to_die);
	sem_post(philo->data->meal_lock);
	return (is_dead);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_death(philo))
		{
			print_status(philo, DIED);
			sem_post(philo->data->stop);
			exit(1);
		}
		usleep(500);
	}
	return (NULL);
}

void	*death_routine(void *arg)
{
	t_wait	*wait_data;

	wait_data = (t_wait *)arg;
	sem_wait(wait_data->data->stop);
	*wait_data->simulation_end = 1;
	sem_post(wait_data->data->death_main);
	return (NULL);
}

void	*meals_routine(void *arg)
{
	t_wait	*wait_data;
	int		i;

	wait_data = (t_wait *)arg;
	i = 0;
	while (i < wait_data->data->num_philos)
	{
		if (*wait_data->simulation_end == 1)
			break ;
		sem_wait(wait_data->data->finished); // wait ici ducoup check pas
		(*wait_data->meals_eaten)++;
		i++;
	}
	sem_post(wait_data->data->stop);
	sem_post(wait_data->data->death_main);
	return (NULL);
}

void	wait_for_processes(t_data *data)
{
	pthread_t	threads[2];
	t_wait		wait_data;
	int			death;
	int			meals_eaten;

	wait_data = init_wait_struct(data, &death, &meals_eaten);
	create_monitor_threads(&wait_data, &threads[0], &threads[1]);
	sem_wait(data->death_main);
	pthread_join(threads[0], NULL);
	if (data->max_meals > 0)
		pthread_join(threads[1], NULL);
	kill_philos(data, 0);
	wait_philos(data, 0);
}
