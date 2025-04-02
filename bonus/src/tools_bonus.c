/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:26:30 by pnaessen          #+#    #+#             */
/*   Updated: 2025/04/02 10:55:40 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	init_simulation(t_data *data, int argc, char **argv, t_philo **philos)
{
	if (init_data(data, argc, argv) != 0)
		return (1);
	if (init_semaphores(data) != 0)
	{
		free(data->pids);
		return (1);
	}
	*philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!*philos)
	{
		free(data->pids);
		return (1);
	}
	return (0);
}

void	cleanup_resources(t_data *data, t_philo *philos)
{
	sem_close(data->forks);
	sem_close(data->write);
	sem_close(data->meal_lock);
	sem_close(data->finished);
	sem_close(data->stop);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_FINISHED);
	sem_unlink(SEM_STOP);
	if (data->pids)
		free(data->pids);
	if (!philos)
		free(philos);
}
