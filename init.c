/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:33:19 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/01 18:44:21 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int init_threads();
{
    return (0);
}

int init_monitor_thread()
{
    return (0);
}

int init_data(char **arguments, t_table **table)
{
    (*table)->number_of_philo = ft_atoll(argument[1]);
    (*table)->time_to_die = ft_atoll(argument[2]);
    (*table)->time_to_eat = ft_atoll(argument[3]);
    (*table)->time_to_sleep = ft_atoll(argument[4]);
    if ((*table)->number_of_philo == ULLONG_MAX
        || (*table)->time_to_die == ULLONG_MAX
        || (*table)->time_to_eat == ULLONG_MAX
        || (*table)->time_to_sleep == ULLONG_MAX)
        return (1);
    (*table)->meals_to_eat = 0; //default, if there is no arg[5]
    if (argument[5])
    {
        (*table)->meals_to_eat = ft_atoll(argument[5]);
        if ((*table)->meals_to_eat == ULLONG_MAX)
            return (1);
    }
    (*table)->simulation_end = false;
    (*table)->fork = NULL;
    (*table)->thread = NULL;
    (*table)->philos = NULL;
    return (0);
}
