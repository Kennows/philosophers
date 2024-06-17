/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinone <mheinone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:23:51 by mheinone          #+#    #+#             */
/*   Updated: 2024/05/29 13:37:11 by mheinone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *str)
{
	long	num;
	int		sign;

	sign = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = 1;
		str++;
	}
	num = 0;
	while (*str >= 48 && *str <= 57)
	{
		num *= 10;
		num += *str - 48;
		str++;
	}
	if (sign == 1)
		num *= -1;
	return (num);
}
