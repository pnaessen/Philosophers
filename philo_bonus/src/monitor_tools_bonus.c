/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_tools_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:01:01 by pn                #+#    #+#             */
/*   Updated: 2025/04/04 14:41:41 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	check_death_condition(t_wait *wait_data)
{
	int	end;

	end = 0;
	pthread_mutex_lock(wait_data->lock);
	if (*(wait_data->simulation_end))
		end = 1;
	pthread_mutex_unlock(wait_data->lock);
	return (end);
}

void	kill_philos(t_data *data, int j)
{
	while (j < data->num_philos)
	{
		kill(data->pids[j], SIGKILL);
		j++;
	}
}

void	wait_philos(t_data *data, int j)
{
	int	status;

	while (j < data->num_philos)
	{
		waitpid(data->pids[j], &status, 0);
		j++;
	}
}

void	init_wait_values(int *death, int *meals_eaten)
{
	*death = 0;
	*meals_eaten = 0;
}

t_wait	init_wait_struct(t_data *data, pthread_mutex_t *mutex, int *death,
		int *meals_eaten)
{
	t_wait	wait_data;

	init_wait_values(death, meals_eaten);
	wait_data.data = data;
	wait_data.simulation_end = death;
	wait_data.meals_eaten = meals_eaten;
	wait_data.lock = mutex;
	return (wait_data);
}
