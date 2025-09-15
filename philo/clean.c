/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:00:36 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/15 10:32:54 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mem(t_table **table)
{
	if ((*table)->threads)
		free((*table)->threads);
	if ((*table)->philos)
		free((*table)->philos);
	if ((*table)->forks)
		free((*table)->forks);
	free(*table);
}

int	destroy_philo_mutex(t_table **table)
{
	unsigned long long	i;

	i = 0;
	while (i < (*table)->numof_philo)
	{
		if (pthread_mutex_destroy(&(*table)->philos[i].philo_mutex) != 0)
			return (1);
		i++;
	}
	return (0);
}

/*MUST NOT destroy mutexes that are used by monitor while monitor thread
 is still going. need to wait for monitor first and then destroy mutexes*/
/*first join all threads, then destroy philo mutexes,
	lastly destroy global mutexes*/
int	join_destroy(t_table **table)
{
	unsigned long long	i;

	i = 0;
	while ((i < (*table)->numof_philo))
	{
		if (pthread_join((*table)->threads[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_join((*table)->monitor, NULL) != 0)
		return (1);
	i = 0;
	while (i < (*table)->numof_philo)
	{
		if (pthread_mutex_destroy(&(*table)->forks[i]) != 0)
			return (1);
		i++;
	}
	if (destroy_philo_mutex(table) != 0)
		return (1);
	if (pthread_mutex_destroy(&(*table)->end_mutex) != 0)
		return (1);
	if (pthread_mutex_destroy(&(*table)->print_mutex) != 0)
		return (1);
	return (0);
}
