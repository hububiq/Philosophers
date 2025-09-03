/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:54:29 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/02 13:50:35 by hgatarek         ###   ########.fr       */
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
    pthread_mutex_t		*left_fork;
    pthread_mutex_t		*right_fork;
    int					last_meal_start;
    int					meals_eaten;

}   t_philo;

typedef struct s_table
{
    unsigned long long  number_of_philo;
    unsigned long long  time_to_die;
    unsigned long long  time_to_eat;
    unsigned long long  time_to_sleep;
    unsigned long long  meals_to_eat;
    pthread_mutex_t     *forks;    //mutexes are essentialy forks!
    bool                simulation_end;
    pthread_t           *threads; //not equal to philosophers.
    t_philo             *philos;
}   t_table;
