/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinone <mheinone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:43:59 by mheinone          #+#    #+#             */
/*   Updated: 2025/01/24 17:54:22 by mheinone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(int philo, char action, t_philos *info)
{
	long			time;

	if (check_stop(info, CHECK) == 1)
		return ;
	pthread_mutex_lock(info->write);
	time = check_time(info, CHECK, 0);
	if (action == 'f')
		printf("%ld %d has taken a fork\n", time, philo);
	if (action == 'e')
		printf("%ld %d is eating\n", time, philo);
	if (action == 's')
		printf("%ld %d is sleeping\n", time, philo);
	if (action == 't')
		printf("%ld %d is thinking\n", time, philo);
	if (action == 'd')
		printf("%ld %d died\n", time, philo);
	pthread_mutex_unlock(info->write);
}

int	check_stop(t_philos *info, int mode)
{
	int	ret;

	pthread_mutex_lock(info->check);
	if (mode == SET)
	{
		info->stop = 1;
		ret = 1;
	}
	if (mode == CHECK)
		ret = info->stop;
	pthread_mutex_unlock(info->check);
	return (ret);
}

int	check_ready(t_philos *info, int mode)
{
	int	ret;

	pthread_mutex_lock(info->check);
	if (mode == SET)
	{
		info->ready++;
		ret = 0;
	}
	if (mode == CHECK)
	{
		if (info->ready == info->philo_count)
			ret = 1;
		else
			ret = 0;
	}
	pthread_mutex_unlock(info->check);
	return (ret);
}
