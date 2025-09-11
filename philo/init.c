/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:33:19 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/10 15:50:57 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*im assigning left and right forks with ampersand because they are not a photocopy! it must be a pointer to the same mutex*/

int init_philos(t_table **table)
{
	unsigned long long	i;
	unsigned long long	quantity;

	quantity = (*table)->numof_philo;
	i = 0;
	while (i < quantity)
	{
		(*table)->philos[i].philo_id = i + 1;
		(*table)->philos[i].meals_eaten = 0;
		(*table)->philos[i].last_meal_time = convert_print_time();
		(*table)->philos[i].left_fork = &(*table)->forks[i];
		if (i == 0)
			(*table)->philos[i].right_fork = &(*table)->forks[quantity - 1];
		else
			(*table)->philos[i].right_fork = &(*table)->forks[i - 1];
		(*table)->philos[i].table = *table;
		if (pthread_mutex_init(&(*table)->philos[i].philo_mutex, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

/*creating mutexes and threads*/
/*philos also malloced here, not locally anywhere else*/

int init_threads_mutexes(t_table **tbl)
{
	unsigned long long	i;
	
	i = 0;
	(*tbl)->philos = malloc(sizeof(t_philo) * ((*tbl)->numof_philo));
	(*tbl)->threads = malloc(sizeof(pthread_t) * ((*tbl)->numof_philo));
	(*tbl)->forks = malloc(sizeof(pthread_mutex_t) * ((*tbl)->numof_philo));
	if (!(*tbl)->philos || !(*tbl)->threads || !(*tbl)->forks)
		return (1);
	while (i < (*tbl)->numof_philo)
	{
		if (pthread_mutex_init(&(*tbl)->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(*tbl)->end_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(*tbl)->print_mutex, NULL) != 0)
	 	return (1);
	if (init_philos(tbl))
        return (printf("Creating threads failed."), free_mem(tbl), 1);
	
	i = 0;
	while (i < (*tbl)->numof_philo)
	{
		if (pthread_create(&(*tbl)->threads[i], NULL, &rout, &(*tbl)->philos[i]))
			return (1);
		i++;
	}
    return (0);
}

/*initialising also mutexes for ending flag and printing here*/

int init_monitor_thread(t_table **tbl)
{
	if (pthread_create(&(*tbl)->monitor, NULL, &monit_routine, *tbl) != 0)
		return (1);
	return (0);
}

int init_data(char **arguments, t_table **table)
{
    (*table)->numof_philo = ft_atoll(arguments[1]);
    (*table)->time_to_die = ft_atoll(arguments[2]);
    (*table)->time_to_eat = ft_atoll(arguments[3]);
    (*table)->time_to_sleep = ft_atoll(arguments[4]);
    if ((*table)->numof_philo == ULLONG_MAX
        || (*table)->time_to_die == ULLONG_MAX
        || (*table)->time_to_eat == ULLONG_MAX
        || (*table)->time_to_sleep == ULLONG_MAX)
        return (1);
    (*table)->meals_to_eat = 0; //default, if there is no arg[5]
    if (arguments[5])
    {
        (*table)->meals_to_eat = ft_atoll(arguments[5]);
        if ((*table)->meals_to_eat == ULLONG_MAX)
            return (1);
    }
	(*table)->full_philos = 0;
    (*table)->simulation_end = false;
    return (0);
}
