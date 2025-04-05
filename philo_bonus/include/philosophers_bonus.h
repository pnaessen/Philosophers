/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:23:02 by pnaessen          #+#    #+#             */
/*   Updated: 2025/04/05 11:43:04 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define RESET "\033[0m"
# define GREEN "\033[32m"
# define BLUE "\033[34m"
# define YELLOW "\033[33m"
# define CYAN "\033[36m"
# define RED "\033[31m"

# define SEM_FORKS "/sem_forks"
# define SEM_WRITE "/sem_write"
# define SEM_MEAL "/sem_meal"
# define SEM_FINISHED "/sem_finished"
# define SEM_STOP "/sem_stop"
# define SEM_DEATH "/sem_death"
# define SEM_MAIN "/sem_main"

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
	int				meals_completed;
	long			start_time;
	pid_t			*pids;
	sem_t			*forks;
	sem_t			*write;
	sem_t			*meal_lock;
	sem_t			*finished;
	sem_t			*stop;
	sem_t			*death_main;
	// sem_t			*meals_main;
}					t_data;

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	pthread_t		monitor_thread;
	long			last_meal;
	int				meals_eaten;
	t_data			*data;
	struct s_wait	*wait;
}					t_philo;

typedef struct s_wait
{
	t_data			*data;
	int				*simulation_end;
	int				*meals_eaten;
}					t_wait;

/////////////////////////////src////////////////////////////////////

////////////////////////////action_bonus.c/////////////////////////
void				init_messages(char *colors[5], char *status_messages[5]);
void				print_status(t_philo *philo, t_status status);
void				update_last_meal(t_philo *philo);

//////////////////////////init_bonus.c///////////////////////////
int					init_data(t_data *data, int argc, char **argv);
void				unlink_semaphores(void);
int					init_semaphores(t_data *data);
void				init_philo(t_philo *philo, int id, t_data *data);
int					create_processes(t_data *data, t_philo *philos);

////////////////////////monitor_bonus.c//////////////////////////
void				*monitor_routine(void *arg);
void				wait_for_processes(t_data *data);
void				*meals_routine(void *arg);
void				*death_routine(void *arg);

////////////////////////monitor_tools_bonus.c//////////////////
int					check_death_condition(t_wait *wait_data);
void				kill_philos(t_data *data, int i);
void				wait_philos(t_data *data, int i);
void				init_wait_values(int *death, int *meals_eaten);
t_wait				init_wait_struct(t_data *data, int *death,
						int *meals_eaten);

////////////////////////routine_bonus.c/////////////////////////
void				take_forks(t_philo *philo);
void				eat_routine(t_philo *philo);
void				sleep_and_think(t_philo *philo);
void				philo_routine(t_philo *philo);

///////////////////////utils_bonus/////////////////////////////
int					check_args(int argc, char **argv);
int					ft_isdigit(char *str);
void				smart_sleep(long duration);
long				get_current_time(void);
int					ft_atoi(const char *str);

/////////////////////tools_bonus.c////////////////////////////
int					init_simulation(t_data *data, int argc, char **argv,
						t_philo **philos);
void				cleanup_resources(t_data *data, t_philo *philos);
int					check_end_condition(t_wait *wait_data);
void				create_monitor_threads(t_wait *wait_data,
						pthread_t *death_thread, pthread_t *meals_thread);

#endif