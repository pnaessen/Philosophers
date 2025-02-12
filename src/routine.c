/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 22:18:13 by pn                #+#    #+#             */
/*   Updated: 2025/02/12 18:31:04 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void    wait_for_start(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->start_lock);
    while (!philo->data->start_flag)
    {
        pthread_mutex_unlock(&philo->data->start_lock);
        usleep(100);
        pthread_mutex_lock(&philo->data->start_lock);
    }
    pthread_mutex_unlock(&philo->data->start_lock);
}

void    *philo_routine(void *arg)
{
    t_philo    *philo;

    philo = (t_philo *) arg;
    update_last_meal(philo);
    wait_for_start(philo);
    if (philo->id % 2 == 0)
        usleep(500);
    while (!should_stop(philo->data))
    {
        eat_routine(philo);
        increment_meals(philo);
        if (should_stop(philo->data))
            break ;
        sleep_and_think(philo);
        if (philo->data->max_meals > 0
            && philo->meals_eaten >= philo->data->max_meals)
            break ;
        usleep(100);
    }
    return (NULL);
}

void	eat_routine(t_philo *philo)
{
	take_forks(philo);
	print_status(philo, EATING);
	update_last_meal(philo);
	smart_sleep(philo->data->time_to_eat, philo->data);
	release_forks(philo);
}
