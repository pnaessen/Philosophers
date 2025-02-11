/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:28:13 by pn                #+#    #+#             */
/*   Updated: 2025/02/11 11:15:45 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (!check_args(argc))
		return (1);
	if (init_simu(&data, argc, argv, &philos) != 0)
		return (1);
	if (create_threads(&data, philos) != 0)
		cleanup_resources(&data, philos, true);
	start_simu(&data);
	join_threads(&data, philos);
	cleanup_resources(&data, philos, true);
	return (0);
}
