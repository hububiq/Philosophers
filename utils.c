/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:33:12 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/09 14:27:06 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/*usleep doesnt need mutex bc it operates on read-only data and doesnt change any shared data*/
/*print DOES need mutex because it not only reads but writes to stdout also, stdout is shared*/
/*mutex is to be performed inside print_status. not around print_status in calling function!!*/
/*important to check if the simulation is going because there shouldn't be "sleeping" msg after death*/
void print_status(t_table *tbl, unsigned long long philo_id, char *msg)
{
	struct timeval t;

	pthread_mutex_lock(&tbl->print_mutex);
	if (is_simulation_going(tbl))
	{

		gettimeofday(&time, NULL);
		printf("%llu %llu %s\n", t.tv_sec*1000 + t.tv_usec/1000, philo_id, msg); //not sure if its gonna be correct timestamp
	}
	pthread_mutex_unlock(&tbl->print_mutex);
}

int is_simulation_going(t_table *table)
{
	phtread_mutex_lock(&table->end_mutex);
	if (table->simulation_end)
	{
		phtread_mutex_unlock(&table->end_mutex);
		return (0);
	}
	else
	{
		phtread_mutex_unlock(&table->end_mutex);
		return (1);
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

