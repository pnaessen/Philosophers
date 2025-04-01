/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 9:17:24 by pnaessen          #+#    #+#             */
/*   Updated: 2025/04/01 14:00:58 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	philos = NULL;
	if (!check_args(argc, argv))
		return (1);
	if (init_simulation(&data, argc, argv, &philos) != 0)
		return (1);
	if (create_processes(&data, philos) != 0)
	{
		cleanup_resources(&data, philos);
		return (1);
	}
	wait_for_processes(&data);
	cleanup_resources(&data, philos);
	return (0);
}
