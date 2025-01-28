/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pn <pn@student.42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:27:20 by pn                #+#    #+#             */
/*   Updated: 2025/01/28 22:01:30 by pn               ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_data
{
	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				max_meals;
	long			start_time;
	bool			simulation_end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	end_lock;
}					t_data;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	long		last_meal;
	int			meals_eaten;
	t_data		*data;
}				t_philo;

int		init_data(t_data *data, int argc, char **argv);
int		init_philos(t_data *data, t_philo **philos);

void	ft_sleep(int ms);
int		ft_atoi(const char *str);

void	print_status(t_philo *philo, char *msg);
void	philo_eat(t_philo *philo);
void	philo_sleep_think(t_philo *philo);

void	*philo_routine(void *arg);
void	*monitor(void *arg);

#endif