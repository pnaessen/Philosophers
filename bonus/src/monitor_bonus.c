/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:40:32 by pnaessen          #+#    #+#             */
/*   Updated: 2025/04/01 17:27:00 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

void	wait_for_processes(t_data *data)
{
	pthread_t		death_thread;
	pthread_t		meals_thread;
	t_wait			wait_data;
	bool			death;
	int				meals_eaten;
	pthread_mutex_t	mutex;

	death = false;
	meals_eaten = 0;
	pthread_mutex_init(&mutex, NULL);
	wait_data.data = data;
	wait_data.simulation_end = &death;
	wait_data.lock = &mutex;
	wait_data.meals_eaten = &meals_eaten;
	// init_wait(&wait_data, data, &death, &meals_eaten);
	pthread_create(&death_thread, NULL, , &wait_data);
	if (data->max_meals > 0)
		pthread_create(&meals_thread, NULL, , &wait_data);
	while (1)
	{
	}
}

// void	init_wait(t_wait *wait_data, t_data *data, bool death, int meals_eaten)
// {
// 	wait_data->data = data;
// 	wait_data->simulation_end = death;
// 	wait_data->lock = &mutex;
// 	wait_data->meals_eaten = meals_eaten;
// }
