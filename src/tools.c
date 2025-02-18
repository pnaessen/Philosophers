/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:54:20 by pnaessen          #+#    #+#             */
/*   Updated: 2025/02/18 11:03:50 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo philo_count t_die t_eat t_sleep [meals]\n");
		return (0);
	}
	while (i < argc)
	{
		if (!argv[i][0])
		{
			printf("empty!!\n");
			return (0);
		}
		if (ft_isdigit(argv[i]) == 0)
		{
			printf("Only digit!!\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_simu(t_data *data, int argc, char **argv, t_philo **philos)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->meals_completed = 0;
	data->simulation_end = false;
	if (init_data(data, argc, argv) != 0 || init_philos(data, philos) != 0)
		return (1);
	data->start_time = get_current_time();
	return (0);
}

void	handle_creation_error(t_data *data, t_philo *philos, int last_index)
{
	set_simulation_end(data);
	while (last_index >= 0)
	{
		pthread_join(philos[last_index].thread, NULL);
		last_index--;
	}
}

int	create_philo_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]))
		{
			printf("Error: Thread creation failed\n");
			return (i);
		}
	}
	return (-1);
}

int	create_threads(t_data *data, t_philo *philos)
{
	int	error_index;

	error_index = create_philo_threads(data, philos);
	if (error_index != -1)
	{
		handle_creation_error(data, philos, error_index);
		return (1);
	}
	if (pthread_create(&data->monitor_thread, NULL, monitor, philos) != 0)
	{
		printf("Error: Monitor thread failed\n");
		set_simulation_end(data);
		handle_creation_error(data, philos, data->num_philos - 1);
		return (1);
	}
	return (0);
}
