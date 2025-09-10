/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:02:09 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/10 16:03:19 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TO_DO   I have potential deadlocks
//TO_DO   also, if every philo is full, they still iterate a little and finish with latency. is it okay? there are still some logs shown
//TO_DO   learn precisely how to read fsanitizer !!

//TO_DO   If convert_print_time can be without arguments?
//TO_DO   clear the functions to 25lines: main, init_threads_mutexes, monit_routine - NORMINETTE
//TO_DO   read about valgrind/helgrind in manual.
//TO_DO   put joining before freeing the table! otherwise threads can't join.

/*important note - if I define in struct pointer to mutex, I need to alocate memory for it and mutex_init.*/
/*if its only object wihtout pointer, it just need ampersand to pass the address of the object (and of course init too)*/

#include "philo.h"

/*check for arguments validity, compare with int max*/

int main(int argc, char **argv)
{
    t_table *table;

    if (argc < 5 || argc > 6)
        return (printf("Wrong input"), 1);
    table = malloc(sizeof(t_table));
    if (!table)
        return (1);
    if (init_data(argv, &table))
        return (printf("Invalid data"), free(table), 1);
    if (table->numof_philo > INT_MAX || table->time_to_die > INT_MAX
        || table->time_to_eat > INT_MAX || table->time_to_sleep > INT_MAX)
        return (printf("Wrong input"), free_mem(&table), 1);
    if (table->numof_philo == 0)
        return (printf("Must have at least one philosopher\n"), 1);
    if (argc == 6)
    {
		if (table->meals_to_eat > INT_MAX)
            return (printf("Wrong input"), free_mem(&table), 1);
	}
    if (init_threads_mutexes(&table))
        return (printf("Creating threads failed."), printf("tutaj: 1"), join_destroy(&table), 1);
    if (init_monitor_thread(&table))
        return (printf("Monit thr. creation failed"), printf("tutaj: 2"), join_destroy(&table), 1);
    if (join_destroy(&table))
		return (printf("Threads joining failed."), free_mem(&table), 1);
	free_mem(&table); //could be moved inside join_destroy. then I dont need ampersand and double pointer because its nothing to pass later on.
	return (0);
}
