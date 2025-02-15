/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:27:20 by pn                #+#    #+#             */
/*   Updated: 2025/02/15 14:56:01 by pnaessen         ###   ########lyon.fr   */
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
	int				start_flag;
	int				meals_completed;
	long			start_time;
	bool			simulation_end;
	pthread_mutex_t	meals_complete_lock;
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
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	long			last_meal;
	int				meals_eaten;
	t_data			*data;
}					t_philo;

/////////actions.c/////
void				print_status(t_philo *philo, t_status status);
void				increment_meals(t_philo *philo);

///////////init.c/////////////
int					init_data(t_data *data, int argc, char **argv);
int					init_philos(t_data *data, t_philo **philos);

//////////monitor.c////////////
bool				check_philo_death(t_philo *philo);
bool				check_any_death(t_philo *philos);
void				*monitor(void *arg);
void				set_simulation_end(t_data *data);

/////////routine.c////////////
void				*philo_routine(void *arg);
void				eat_routine(t_philo *philo);
void				wait_for_start(t_philo *philo);
void				handle_nietzsche(t_philo *philo);

/////////time.c////////////
long				get_current_time(void);
long				get_ms_since_start(t_data *data);
void				smart_sleep(long duration, t_data *data);
void				sleep_and_think(t_philo *philo);

////////////utils.c///////////
int					ft_atoi(const char *str);
bool				should_stop(t_data *data);
void				update_last_meal(t_philo *philo);
bool				check_all_meals_complete(t_data *data);
void				cleanup_resources(t_data *data, t_philo *philos, bool exit);

/////////////tools.c///////////
int					check_args(int argc);
int					init_simu(t_data *data, int argc, char **argv,
						t_philo **philos);
int					create_threads(t_data *data, t_philo *philos);
void				start_simu(t_data *data);
void				join_threads(t_data *data, t_philo *philos);

#endif