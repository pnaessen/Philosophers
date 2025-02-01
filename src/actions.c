/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pn <pn@student.42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 22:17:52 by pn                #+#    #+#             */
/*   Updated: 2025/02/01 19:50:16 by pn               ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    print_status(t_philo *philo, char *msg)
{
    long    timestamp;

    pthread_mutex_lock(&philo->data->write_lock);
    if (!philo->data->simulation_end)
    {
        timestamp = get_current_time() - philo->data->start_time;
        if (strcmp(msg, "died") == 0)
            printf(RED"[%5ld ms] Philosopher %d %s 💀"RESET"\n", 
                timestamp, philo->id, msg);
        else if (strcmp(msg, "is eating") == 0)
            printf(GREEN"[%5ld ms] Philosopher %d %s 🍝"RESET"\n", 
                timestamp, philo->id, msg);
        else if (strcmp(msg, "is sleeping") == 0)
            printf(BLUE"[%5ld ms] Philosopher %d %s 😴"RESET"\n", 
                timestamp, philo->id, msg);
        else if (strcmp(msg, "is thinking") == 0)
            printf(YELLOW"[%5ld ms] Philosopher %d %s 🤔"RESET"\n", 
                timestamp, philo->id, msg);
        else if (strstr(msg, "fork") != NULL)
            printf(CYAN"[%5ld ms] Philosopher %d %s 🍴"RESET"\n", 
                timestamp, philo->id, msg);
    }
    pthread_mutex_unlock(&philo->data->write_lock);
}

void    take_forks(t_philo *philo)
{
    int first_fork;
    int second_fork;


    first_fork = philo->id - 1;
    second_fork = philo->id % philo->data->num_philos;

    if (first_fork > second_fork)
    {
        int temp = first_fork;
        first_fork = second_fork;
        second_fork = temp;
    }

    pthread_mutex_lock(&philo->data->forks[first_fork]);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(&philo->data->forks[second_fork]);
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


// void    take_forks(t_philo *philo)
// {
//     if (philo->id % 2)
//     {
//         pthread_mutex_lock(&philo->data->forks[(philo->id - 1) % philo->data->num_philos]);
//         print_status(philo, "has taken a fork");
//         pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->num_philos]);
//         print_status(philo, "has taken a fork");
//     }
//     else
//     {
//         pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->num_philos]);
//         print_status(philo, "has taken a fork");
//         pthread_mutex_lock(&philo->data->forks[(philo->id - 1) % philo->data->num_philos]);
//         print_status(philo, "has taken a fork");
//     }
// }
