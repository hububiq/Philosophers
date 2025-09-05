/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:33:19 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/05 16:23:36 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int init_philos(t_table **table)
{
	int					i;
	struct timeval		time;
	unsigned long long	quantity;

	quantity = (*table)->number_of_philo;
	i = 0;
	(*table)->philos = malloc(sizeof(t_philo) * quantity);
	if (!(*table)->philos)
		return (1);
	while (i < quantity)
	{
		(*table)->philos[i].philo_id = i + 1;
		(*table)->philos[i].meals_eaten = 0;
		(*table)->philos[i].last_meal_time = convert_print_time();
		(*table)->philos[i].left_fork = &(*table)->forks[i];
		if (i == 0)
			(*table)->philos[i].right_fork = &(*table)->forks[quantity - 1]; //ampersand! im giving the address, not assiging copy
		else
			(*table)->philos[i].right_fork = &(*table)->forks[i - 1];
		(*table)->philos[i].table = *table;
		if (pthread_mutex_init(&(*table)->philos[i].philo_mutex, NULL) != 0)
			return (1);
		i++;
	}
}

/*creating mutexes and threads*/
int init_threads_mutexes(t_table **tbl)
{
	int				i;
	pthread_t		*threads_arr;
	pthread_mutex_t	*forks;
	
	i = 0;
	init_philos(tbl);
	(*tbl)->threads = malloc(sizeof(pthread_t) * ((*tbl)->number_of_philo));
	if (!(*tbl)->threads)
		return (1);
	(*tbl)->forks = malloc(sizeof(pthread_mutex_t) * ((*tbl)->number_of_philo));
	if (!(*tbl)->forks)
		return (1);
	forks = (*tbl)->forks;
	threads_arr = (*tbl)->threads;
	while (i < (*tbl)->number_of_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (1);
		i++;
	}
	while (i < (*tbl)->number_of_philo)
	{
		if (pthread_create(&threads_arr[i], NULL, &rout, &(*tbl)->philos[i]))
			return (1);
		i++;
	}
    return (0);
}

/*initialising also mutexes for ending flag and printing here*/
int init_monitor_thread(t_table **tbl)
{
	if (pthread_mutex_init(&(*tbl)->end_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(*tbl)->print_mutex, NULL) != 0)
		return (1);
	if (pthread_create(&(*tbl)->monitor, NULL, &monit_routine, *tbl) != 0)
		return (1);
	return (0);
}

int init_data(char **arguments, t_table **table)
{
    (*table)->number_of_philo = ft_atoll(arguments[1]);
    (*table)->time_to_die = ft_atoll(arguments[2]);
    (*table)->time_to_eat = ft_atoll(arguments[3]);
    (*table)->time_to_sleep = ft_atoll(arguments[4]);
    if ((*table)->number_of_philo == ULLONG_MAX
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
    //(*table)->forks = NULL;
    //(*table)->threads = NULL;
    //(*table)->philos = NULL;
	//(*table)->monitor = NULL;
	//(*table)->end_mutex = NULL;
	//(*table)->print_mutex = NULL;
    return (0);
}
