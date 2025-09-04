/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:54:29 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/04 17:25:44 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/syscall.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <stdbool.h>

typedef struct s_philo
{
    int					philo_id;
    t_table				*table;
    pthread_mutex_t		left_fork;
    pthread_mutex_t		right_fork;
    unsigned long long	last_meal_time;
    int					meals_eaten; //***
}   t_philo;

typedef struct s_table
{
    unsigned long long  number_of_philo;
    unsigned long long  time_to_die;
    unsigned long long  time_to_eat;
    unsigned long long  time_to_sleep;
    unsigned long long  meals_to_eat;
	unsigned long long	full_philos; //*** 
    pthread_mutex_t     *forks;    //mutexes are essentialy forks!
    bool                simulation_end;
	pthread_mutex_t		*end_mutex;
    pthread_t           *threads; //not equal to philosophers.
	pthread_t			monitor;
	pthread_mutex_t		*monit_mutex;
    t_philo             *philos;
}   t_table;

void				*routine(void *argument);
void				monitor_routine(void *argument);
unsigned long long	convert_print_time();
int					is_simulation_going(t_table **table);