/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:38:27 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/04 17:40:47 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *argument)
{
	t_table 			*table;
	int					i;

	i = 0;
	table = (t_table *)argument;
	while (i < table->number_of_philo)  //equaling the time
	{
		table->philos[i].last_meal_time = convert_print_time();
		i++;
	}
	if (table->philos->philo_id % 2)
		usleep(1000);
	while (is_simulation_going(&table))
	{	
		//eat function (first pick fork - mutex_lock (one of philo[i] and one of philo[i - 1]))
		//sleep function
		//think function
	}
}

/* this function constantly checking if the philo died.*/
void	monitor_routine(void *argument)
{
	t_table 			*table;
	int					i;
	unsigned long long	current_time;

	i = 0;
	current_time = 0;
	table = (t_table *)argument;
	while (1)
	{
		if (i < table->number_of_philo)
		{
			pthread_mutex_lock(&table->monit_mutex);
			if ((convert_print_time() - table->philos[i].last_meal_time) > table->time_to_die)
				table->simulation_end = 1;
			pthread_mutex_unlock(&table->monit_mutex);
			i++;
		}
		i++;
		if (!is_simulation_going(&table))  //does monitoring thread sets it? or its just checking for it?
			break;
		usleep(1000); //little busy-wait to relax CPU
		
		/*the check if all philos are full*/
	}	
}
