/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinone <mheinone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:44:15 by mheinone          #+#    #+#             */
/*   Updated: 2025/01/24 21:07:12 by mheinone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	current;
	long			time;

	gettimeofday(&current, NULL);
	time = current.tv_sec * 1000 + (long)(current.tv_usec / 1000);
	return (time);
}

long	check_time(t_philos *info, int mode, int i)
{
	long			time;

	pthread_mutex_lock(info->check);
	time = get_time();
	if (mode == SET)
		*info->timer[i] = time - *info->timer[0];
	if (mode == CHECK)
	{
		if (i == 0)
			time = time - *info->timer[0];
		else
			time = *info->timer[i];
	}
	pthread_mutex_unlock(info->check);
	return (time);
}

void	ft_sleep(t_philos *info, int sleep_time)
{
	long	wake_up;

	wake_up = get_time() + ((long)sleep_time);
	while (get_time() <= wake_up)
	{
		if (check_stop(info, CHECK) == 1)
			break ;
		usleep(200);
	}
}
