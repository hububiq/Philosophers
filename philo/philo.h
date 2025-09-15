/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:54:29 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/15 10:45:22 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/syscall.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>

//typedef alias vs struct tag name
/*forward declaration because of circular structures' dependencies*/
struct	s_philo;
typedef struct s_table
{
	unsigned long long	numof_philo;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	meals_to_eat;
	unsigned long long	full_philos;
	unsigned long long	simulation_start;
	bool				simulation_end;
	pthread_t			*threads;
	pthread_t			monitor;
	pthread_mutex_t		*forks;
	pthread_mutex_t		end_mutex;
	pthread_mutex_t		print_mutex;
	struct s_philo		*philos;
}	t_table;

typedef struct s_philo
{
	unsigned long long	philo_id;
	unsigned long long	meals_eaten;
	t_table				*table;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		philo_mutex;
	unsigned long long	last_meal_time;
}	t_philo;

//main.c
int					compare_int(t_table *table);
int					main(int argc, char **argv);

//init.c
void				start_timer(t_table **tbl);
int					init_philos(t_table **table);
int					init_threads_mutexes(t_table **tbl);
int					init_monitor_thread(t_table **tbl);
int					init_data(char **arguments, t_table **table);

//mem_mutexes.c
int					allocate_mem(t_table **tbl);
int					init_mutexes(t_table **tbl);

//routines.c
void				*rout(void *argument);
int					inside_loop(t_table *table);
void				*monit_routine(void *argument);

// routines_functions.c
void				philo_eating(t_philo *philo);
void				philo_sleeping(t_philo *philo);
void				philo_thinking(t_philo *philo);
void				pick_up_forks(t_philo *philo);

// clean.c
void				free_mem(t_table **table);
int					destroy_philo_mutex(t_table **table);
int					join_destroy(t_table **table);

// utils.c
void				print_status(t_table *tbl,
						unsigned long long philo_id, char *msg);
int					is_simulation_going(t_table *table);
unsigned long long	convert_print_time(void);
unsigned long long	ft_atoll(char *str);
void				custom_usleep(unsigned long long time);
#endif