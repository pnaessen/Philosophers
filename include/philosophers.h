/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:27:20 by pn                #+#    #+#             */
/*   Updated: 2025/02/03 13:32:04 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define RESET "\033[0m"
# define GREEN "\033[32m"
# define BLUE "\033[34m"
# define YELLOW "\033[33m"
# define CYAN "\033[36m"
# define RED "\033[31m"

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKING_FORK,
	DIED
}					t_status;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				threads_ready;
	long			start_time;
	bool			simulation_end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	end_lock;
	pthread_mutex_t	start_lock;
	pthread_t		monitor_thread;
}					t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			last_meal;
	int				meals_eaten;
	t_data			*data;
}					t_philo;

// Initialisation
int					init_data(t_data *data, int argc, char **argv);
int					init_philos(t_data *data, t_philo **philos);

// Utilitaires
long				get_current_time(void);
void				ft_sleep(int ms);
int					ft_atoi(const char *str);
void				print_status(t_philo *philo, t_status status);

void				*philo_routine(void *arg);
void				take_forks(t_philo *philo);
void				release_forks(t_philo *philo);
void				philo_eat(t_philo *philo);

// Monitoring
void				*monitor(void *arg);
bool				check_philo_death(t_philo *philo);
bool				check_meals_complete(t_data *data, t_philo *philos);
#endif