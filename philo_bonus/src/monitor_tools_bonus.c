/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_tools_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pn <pn@student.42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:01:01 by pn                #+#    #+#             */
/*   Updated: 2025/04/05 15:24:54 by pn               ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

t_wait	init_wait_struct(t_data *data, int *death, int *meals_eaten)
{
	t_wait	wait_data;

	init_wait_values(death, meals_eaten);
	wait_data.data = data;
	wait_data.simulation_end = death;
	wait_data.meals_eaten = meals_eaten;
	return (wait_data);
}
