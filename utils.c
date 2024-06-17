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
	struct timeval	current;
	long			sec;
	int				usec;
	long			time;

	if (info->stop == 1)
		return ;
	pthread_mutex_lock(info->locks[0]);
	gettimeofday(&current, NULL);
	sec = ((current.tv_sec - info->timer[0]->tv_sec) * 1000);
	usec = ((current.tv_usec - info->timer[0]->tv_usec) / 1000);
	time = sec + (long)usec;
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
	pthread_mutex_unlock(info->locks[0]);
}
