/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:02:09 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/15 10:47:51 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//CAN'T init mutexes after threads creation, they use those 
//in routine! its data race

//if I define in the structure pointer to mutex, I need to alocate
//memory for it and mutex_init
//if its only object wihtout pointer, it just need ampersand to pass the
//address of the object (and of course init too)

#include "philo.h"

int	compare_int(t_table *table)
{
	if (table->numof_philo > INT_MAX || table->time_to_die > INT_MAX
		|| table->time_to_eat > INT_MAX || table->time_to_sleep > INT_MAX)
		return (printf("Wrong input"), free_mem(&table), 1);
	if (table->numof_philo == 0)
		return (printf("Must have at least one philosopher\n"), 1);
	return (0);
}

/*check for arguments validity, compare with int max*/
int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc < 5 || argc > 6)
		return (printf("Wrong input"), 1);
	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	if (init_data(argv, &table))
		return (printf("Invalid data"), free(table), 1);
	compare_int(table);
	if (argc == 6)
	{
		if (table->meals_to_eat > INT_MAX)
			return (printf("Wrong input"), free_mem(&table), 1);
	}
	init_threads_mutexes(&table);
	if (join_destroy(&table))
		return (printf("Threads joining failed."), free_mem(&table), 1);
	free_mem(&table);
	return (0);
}
