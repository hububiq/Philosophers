/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgatarek <hgatarek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:33:12 by hgatarek          #+#    #+#             */
/*   Updated: 2025/09/01 18:43:59 by hgatarek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned long long ft_atoll(char *str) //ull to prevent overflowing in parseing.
{
    int                 i;
    unsigned long long  number; //defined like this, i assume user will enter positive number. if not, it will return ULLONG_MAX

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
