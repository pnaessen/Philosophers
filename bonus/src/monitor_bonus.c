/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:40:32 by pnaessen          #+#    #+#             */
/*   Updated: 2025/04/03 15:11:26 by pnaessen         ###   ########lyon.fr   */
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
	pthread_mutex_lock(wait_data->lock);
	*wait_data->simulation_end = 1;
	pthread_mutex_unlock(wait_data->lock);
	sem_post(wait_data->data->finished);
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
		pthread_mutex_lock(wait_data->lock);
		if ((*wait_data->simulation_end) == 1)
		{
			pthread_mutex_unlock(wait_data->lock);
			return (NULL);
		}
		pthread_mutex_unlock(wait_data->lock);
		sem_wait(wait_data->data->finished);
		pthread_mutex_lock(wait_data->lock);
		(*wait_data->meals_eaten)++;
		pthread_mutex_unlock(wait_data->lock);
		i++;
	}
	sem_post(wait_data->data->stop);
	return (NULL);
}

void	wait_for_processes(t_data *data)
{
	pthread_t		death_thread;
	pthread_t		meals_thread;
	t_wait			wait_data;
	int				death;
	int				meals_eaten;
	pthread_mutex_t	mutex;
	int				i;
	int				status;

	i = 0;
	death = 0;
	meals_eaten = 0;
	pthread_mutex_init(&mutex, NULL);
	wait_data.data = data;
	wait_data.simulation_end = &death;
	wait_data.lock = &mutex;
	wait_data.meals_eaten = &meals_eaten;
	pthread_create(&death_thread, NULL, death_routine, &wait_data);
	if (data->max_meals > 0)
		pthread_create(&meals_thread, NULL, meals_routine, &wait_data);
	while (1)
	{
		pthread_mutex_lock(wait_data.lock);
		if (death || (data->max_meals > 0 && meals_eaten >= data->num_philos))
		{
			pthread_mutex_unlock(wait_data.lock);
			break ;
		}
		pthread_mutex_unlock(wait_data.lock);
	}
	while (i < data->num_philos)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		waitpid(data->pids[i], &status, 0);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	pthread_join(death_thread, NULL);
	if (data->max_meals > 0)
		pthread_join(meals_thread, NULL);
}
