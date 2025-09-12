/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:38:27 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/12 17:18:41 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *rout(void *argument)
{
	t_philo 			*philo;

	philo = (t_philo *)argument;
	if (philo->table->numof_philo == 1)
    {
        print_status(philo->table, philo->philo_id, "has taken a fork");
        custom_usleep(philo->table->time_to_die);
        return (NULL);
    }
	if (philo->philo_id % 2)
		usleep(15);
	while (is_simulation_going(philo->table))
	{	
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	return (NULL);
}

/* this function constantly checking if the philo died.*/
void	*monit_routine(void *argument)
{
	t_table 			*table;
	unsigned long long	i;
	unsigned long long	current_time;

	i = 0;
	current_time = 0;
	table = (t_table *)argument;
	while (1)
	{
		i = 0;
		while (i < table->numof_philo)
		{
			pthread_mutex_lock(&table->philos[i].philo_mutex);
			if ((convert_print_time() - table->philos[i].last_meal_time) > table->time_to_die)
			{
				print_status(table, table->philos[i].philo_id, "died");  //i changed it to here instead of being after table->simu = 1
				pthread_mutex_lock(&table->end_mutex);
				table->simulation_end = 1;
				pthread_mutex_unlock(&table->end_mutex);
				pthread_mutex_unlock(&table->philos[i].philo_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&table->philos[i].philo_mutex);
			i++;
		}
		pthread_mutex_lock(&table->end_mutex);
		if (table->full_philos == table->numof_philo)
			table->simulation_end = true;
		pthread_mutex_unlock(&table->end_mutex);
		if (!is_simulation_going(table))
			break;
		usleep(30); //little busy-wait to relax CPU/
	}
	return (NULL);
}
