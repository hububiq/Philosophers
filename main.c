/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:02:09 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/01 18:51:01 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*check for arguments validity, compare with int max*/
/*create n thread in a loop, n descending from argv[1]*/

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
        return (printf("Wrong input"), free(table), 1)
    if (table->number_of_philo == 0)
        return (printf("Must have at least one philosopher\n"), 1);
    if (argc == 6)
    {
        if (table->meals_to_eat > INT_MAX)
            return (printf("Wrong input"), free(table), 1);
    }
    if (init_threads())
        return (printf("Malloc failed"), free(table), 1);
    if (init_monitor_thread())
        return (printf("Malloc failed"), free(table), 1);
    //join threads
    //destroy threads
    free(table);
}
