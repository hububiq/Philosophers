/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:02:09 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/05 16:23:37 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//TO_DO   printf also need to have their own mutex.
//TO_DO	  implement print_status - set output messages nicely and MUTEX EVERY PRINTF
//TO_D0   implement every activity in routine ! 
//TO_DO   consider initiating every mutex in one big function, so far I initiate in random places.
//TO_DO	  create helper function to print status (lock every printf)

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
        return (printf("Invalid data"), 1);
    if (table->number_of_philo > INT_MAX || table->time_to_die > INT_MAX
        || table->time_to_eat > INT_MAX || table->time_to_sleep > INT_MAX)
        return (printf("Wrong input"), free_mem(&table), 1);
    if (table->number_of_philo == 0)
        return (printf("Must have at least one philosopher\n"), 1);
    if (argc == 6)
    {
        if (table->meals_to_eat > INT_MAX)
            return (printf("Wrong input"), free_mem(&table), 1);
    }
    if (init_threads_mutexes(&table))
        return (printf("Creating threads failed."), free_mem(&table), 1);
	if (init_philos(&table))
        return (printf("Creating threads failed."), free_mem(&table), 1);
    if (init_monitor_thread(&table))
        return (printf("Monit thr. creation failed"), free_mem(&table), 1);
	//here should be some function that start simulation? Aand equals the last meal time.
    if (join_destroy(&table))
        return (printf("Threads joining failed."), free_mem(&table), 1);
	free_mem(&table);
}
