/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_mutexes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:39:39 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/15 10:49:26 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate_mem(t_table **tbl)
{
	(*tbl)->philos = malloc(sizeof(t_philo) * ((*tbl)->numof_philo));
	(*tbl)->threads = malloc(sizeof(pthread_t) * ((*tbl)->numof_philo));
	(*tbl)->forks = malloc(sizeof(pthread_mutex_t) * ((*tbl)->numof_philo));
	if (!(*tbl)->philos || !(*tbl)->threads || !(*tbl)->forks)
		return (1);
	return (0);
}

/*initialising mutexes for ending flag and printing*/
int	init_mutexes(t_table **tbl)
{
	unsigned long long	i;

	i = 0;
	while (i < (*tbl)->numof_philo)
	{
		if (pthread_mutex_init(&(*tbl)->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(*tbl)->end_mutex, NULL) != 0
		|| pthread_mutex_init(&(*tbl)->print_mutex, NULL) != 0)
		return (1);
	return (0);
}
