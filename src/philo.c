/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:28:13 by pn                #+#    #+#             */
/*   Updated: 2025/02/14 13:09:35 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_simu(t_data *data)
{
	pthread_mutex_lock(&data->start_lock);
	data->start_flag = 1;
	pthread_mutex_unlock(&data->start_lock);
}

void	join_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
		pthread_join(philos[i].thread, NULL);
	pthread_join(data->monitor_thread, NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	philos = NULL;
	if (!check_args(argc))
		return (1);
	if (init_simu(&data, argc, argv, &philos) != 0)
		return (1);
	if (create_threads(&data, philos) != 0)
	{
		cleanup_resources(&data, philos, true);
		return (1);
	}
	start_simu(&data);
	join_threads(&data, philos);
	cleanup_resources(&data, philos, true);
	return (0);
}
