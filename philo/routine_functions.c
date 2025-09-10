/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:00:02 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/10 15:29:53 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);  //without ampersand - passing directly . not a pointer!!!
	print_status(philo->table, philo->philo_id, "picks up left fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo->table, philo->philo_id, "picks up right fork");
	pthread_mutex_lock(&philo->philo_mutex);
	print_status(philo->table, philo->philo_id, "is eating");
	usleep(philo->table->time_to_eat * 1000);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->table->meals_to_eat)
	{
		pthread_mutex_lock(&philo->table->end_mutex);
		philo->table->full_philos++;
		pthread_mutex_unlock(&philo->table->end_mutex);
	}	
	pthread_mutex_unlock(&philo->philo_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	
	return ;
}

/*no need to mutex here, print_status has its own, I only usleep, I dont access shared changeable data*/
void philo_sleeping(t_philo *philo)
{
	print_status(philo->table, philo->philo_id, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
	return ;
}

void philo_thinking(t_philo *philo)
{
	print_status(philo->table, philo->philo_id, "is thinking");
	return ;
}
