/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:00:02 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/15 10:50:56 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->table, philo->philo_id, "picks up left fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo->table, philo->philo_id, "picks up right fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo->table, philo->philo_id, "picks up right fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->table, philo->philo_id, "picks up left fork");
	}
}

//I was thinking to put away forks in reversed order based on modulo,
//	but its not necessary
void	philo_eating(t_philo *philo)
{
	pick_up_forks(philo);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal_time = convert_print_time();
	pthread_mutex_unlock(&philo->philo_mutex);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->philo_mutex);
	pthread_mutex_lock(&philo->philo_mutex);
	if (philo->table->meals_to_eat > 0
		&& philo->meals_eaten == philo->table->meals_to_eat)
	{
		pthread_mutex_lock(&philo->table->end_mutex);
		philo->table->full_philos++;
		pthread_mutex_unlock(&philo->table->end_mutex);
	}
	pthread_mutex_unlock(&philo->philo_mutex);
	print_status(philo->table, philo->philo_id, "is eating");
	custom_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

//no need to mutex here, print_status has its own, I only usleep, 
//	I dont access shared, changeable data
void	philo_sleeping(t_philo *philo)
{
	print_status(philo->table, philo->philo_id, "is sleeping");
	custom_usleep(philo->table->time_to_sleep);
}

void	philo_thinking(t_philo *philo)
{
	print_status(philo->table, philo->philo_id, "is thinking");
}
