/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:54:29 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/05 16:09:53 by hgatarek         ###   ########.fr       */
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
	int					meals_eaten;
    t_table				*table;
    pthread_mutex_t		*left_fork;
    pthread_mutex_t		*right_fork;
	pthread_mutex_t		*philo_mutex;
    unsigned long long	last_meal_time;
}   t_philo;

typedef struct s_table
{
    unsigned long long  number_of_philo;
    unsigned long long  time_to_die;
    unsigned long long  time_to_eat;
    unsigned long long  time_to_sleep;
    unsigned long long  meals_to_eat;
	unsigned long long	full_philos;
    pthread_mutex_t     *forks;    //fork are essentialy mutexes!
    bool                simulation_end;
	pthread_mutex_t		*end_mutex;
    pthread_t           *threads;
	pthread_t			monitor;
	pthread_mutex_t		*print_mutex;
    t_philo             *philos;
}   t_table;

void				*rout(void *argument);
void				monit_routine(void *argument);
unsigned long long	convert_print_time();
int					is_simulation_going(t_table **table);
void				philo_eating(t_table **table);
void				philo_sleeping(t_table **table);
void				philo_thinking(t_table **table);