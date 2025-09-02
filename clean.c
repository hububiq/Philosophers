/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:00:36 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/02 13:50:31 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void free_mem(t_table **table)
{
	if ((*table)->threads)
		free((*table)->threads);
	if ((*table)->philos)
		free((*table)->philos);
	if ((*table)->forks)
		free((*table)->forks);
    free(table);
}

int	join_destroy(t_table **table)
{
	int				i;
	pthread_t		*threads_array;
	pthread_mutex_t	*forks;
		
	i = 0;
	forks = (*table)->forks;
	threads_array = (*table)->threads;
	while (threads_array[i])
	{
		
		if (pthread_join(threads_array[i], NULL) != 0)
			return (1);
		if (pthread_mutex_destroy(&forks[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}