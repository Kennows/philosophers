/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinone <mheinone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:43:59 by mheinone          #+#    #+#             */
/*   Updated: 2024/06/17 15:44:15 by mheinone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(int philo, char action, t_philos *info)
{
	long			time;

	if (check_stop(info) == 1)
		return ;
	pthread_mutex_lock(info->write);
	time = get_time(info);
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

void	set_stop(t_philos *info)
{
	pthread_mutex_lock(info->check);
	info->stop = 1;
	pthread_mutex_unlock(info->check);
}

void	set_ready(t_philos *info)
{
	pthread_mutex_lock(info->check);
	info->ready++;
	pthread_mutex_unlock(info->check);
}

int	check_stop(t_philos *info)
{
	int	ret;

	pthread_mutex_lock(info->check);
	ret = info->stop;
	pthread_mutex_unlock(info->check);
	return (ret);
}

long	get_time(t_philos *info)
{
	struct timeval	current;
	long	time;

	pthread_mutex_lock(info->check);
	gettimeofday(&current, NULL);
	time = current.tv_sec * 1000 + (long)(current.tv_usec / 1000);
	pthread_mutex_unlock(info->check);
	return (time - *info->timer[0]);
}
