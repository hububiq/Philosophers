/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:33:12 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/05 16:23:33 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void print_status()
{
	
}

int is_simulation_going(t_table *table)
{
	phtread_mutex_lock(table->end_mutex);
	if (table->simulation_end)
	{
		phtread_mutex_unlock(table->end_mutex);
		return (1);
	}
	else
	{
		phtread_mutex_unlock(table->end_mutex);
		return (0);
	}
}

/*timeval struct consists of tv_sec in seconds and microseconds.
decided to conver to miliseconds.*/
unsigned long long convert_print_time()
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
	{
		printf("Time counter failed");
		return (0);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}


/* Type ull to prevent overflowing in parseing.*/
unsigned long long ft_atoll(char *str)
{
    int                 i;
    unsigned long long  number;

    i = 0;
    number = 0;
    while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
        i++;
    if (str[i] == '+')
        i++;
    if (str[i] == '\0')
        return (ULLONG_MAX);
    while (str[i] && str[i] >= '0' && str[i] <= '9')
    {
        number = number * 10 + (str[i] - 48);
        i++;
    }
    if (str[i] != '\0')
        return (ULLONG_MAX);
    return (number);
}

