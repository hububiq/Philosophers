/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:33:19 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/02 13:50:27 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void *routine(t_philo *philos)
{
			
}

/*creating threads and mutexes. PHILOS STRUCTURE STILL TO INITIALISE. THEY DONT PRECISELY EQUAL TO THREADS.*/

int init_threads_mutexes(t_table **table)
{
	int				i;
	pthread_t		*threads_array;
	pthread_mutex_t	*forks;
	
	i = 0;
	(*table)->threads = malloc(sizeof(pthread_t) * ((*table)->number_of_philo + 1));
	if (!(*table)->threads)
		return (1);
	(*table)->forks = malloc(sizeof(pthread_mutex_t) * ((*table)->number_of_philo + 1));
	if (!(*table)->threads)
		return (1);
	forks = (*table)->forks; 			//is it assignable if its not set to any value?
	threads_array = (*table)->threads;	//is it assignable if its not set to any value?
	while (i < (*table)->number_of_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (1);
		if (pthread_create(threads_array[i], NULL, &routine, &(*table)->philos[i]) != 0);
			return (1);
		i++;
	}
    return (0);
}

int init_monitor_thread()
{
    return (0);
}

int init_philos(t_table **table)
{
	t_philo	*philosopher;
	int		i;

	i = 0;
	
	while (i < (*table)->number_of_philo)
	{
		philosopher = malloc(sizeof(t_philo));
		if (!philosopher)
			return (1);
		((*table)->philos)[i] = philosopher;
		philosopher->philo_id = i;
		i++;
	}
	
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
    (*table)->simulation_end = false;
    (*table)->forks = NULL;
    (*table)->threads = NULL;
    (*table)->philos = NULL;
    return (0);
}
