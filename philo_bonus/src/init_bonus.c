/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pn <pn@student.42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:25:16 by pnaessen          #+#    #+#             */
/*   Updated: 2025/04/23 17:53:03 by pn               ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->max_meals = -1;
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	data->meals_completed = 0;
	data->pids = malloc(sizeof(pid_t) * data->num_philos);
	if (!data->pids || data->num_philos <= 0 || (argc == 6
			&& data->max_meals <= 0))
	{
		if (data->pids)
			free(data->pids);
		return (1);
	}
	data->start_time = get_current_time();
	return (0);
}

int	init_semaphores(t_data *data)
{
	unlink_semaphores();
	data->forks = sem_open(SEM_FORKS, O_CREAT, 0644, data->num_philos);
	data->write = sem_open(SEM_WRITE, O_CREAT, 0644, 1);
	data->meal_lock = sem_open(SEM_MEAL, O_CREAT, 0644, 1);
	data->finished = sem_open(SEM_FINISHED, O_CREAT, 0644, 0);
	data->stop = sem_open(SEM_STOP, O_CREAT, 0644, 0);
	data->death_main = sem_open(SEM_DEATH, O_CREAT, 0644, 0);
	data->meals_main = sem_open(SEM_MAIN, O_CREAT, 0644, 1);
	if (data->forks == SEM_FAILED || data->write == SEM_FAILED
		|| data->meal_lock == SEM_FAILED || data->finished == SEM_FAILED
		|| data->stop == SEM_FAILED || data->death_main == SEM_FAILED
		|| data->meals_main == SEM_FAILED)
		return (1);
	return (0);
}

void	init_philo(t_philo *philo, int id, t_data *data)
{
	philo->id = id + 1;
	philo->pid = -1;
	philo->last_meal = data->start_time;
	philo->meals_eaten = 0;
	philo->data = data;
}

void	kill_philos_fail(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		kill(data->pids[j], SIGKILL);
		j++;
	}
}

int	create_processes(t_data *data, t_philo *philos)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (++i < data->num_philos)
	{
		init_philo(&philos[i], i, data);
		pid = fork();
		if (pid < 0)
		{
			kill_philos_fail(data, i);
			return (1);
		}
		if (pid == 0)
		{
			philo_routine(&philos[i]);
			exit(0);
		}
		else
		{
			philos[i].pid = pid;
			data->pids[i] = pid;
		}
	}
	return (0);
}
