/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:38:27 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/08 14:57:16 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *rout(void *argument)
{
	t_philo 			*philo;

	philo = (t_philo *)argument;
	if (philo->philo_id % 2)
		usleep(1000);
	while (is_simulation_going(philo->table))
	{	
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	return (NULL);
}

/* this function constantly checking if the philo died.*/
void	monit_routine(void *argument)
{
	t_table 			*table;
	int					i;
	unsigned long long	current_time;
	int					everyone_full;

	everyone_full = 0;
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
				pthread_mutex_lock(&table->end_mutex);
				table->simulation_end = 1;
				pthread_mutex_unlock(&table->end_mutex);
				print_status(table, table->philos[i].philo_id, "died");
				pthread_mutex_unlock(&table->philos[i].philo_mutex);
				break;
			}
			pthread_mutex_unlock(&table->philos[i].philo_mutex);
			i++;
		}
		pthread_mutex_lock(&table->end_mutex);
		if (table->full_philos == table->numof_philo)
		{
			everyone_full = 1;
			table->simulation_end = 1;
		}
		pthread_mutex_unlock(&table->end_mutex);
		if (!is_simulation_going(table) || everyone_full) 
			break;
		usleep(1000); //little busy-wait to relax CPU/
	}	
}
