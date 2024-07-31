/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinone <mheinone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:45:01 by mheinone          #+#    #+#             */
/*   Updated: 2024/06/17 15:49:35 by mheinone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philos *info, t_personal *data)
{
	if (pthread_mutex_lock(info->locks[data->id]) == 0 && \
			pthread_mutex_lock(info->locks[data->right_fork]) == 0)
	{
		print_status(data->id, 'f', info);
		print_status(data->id, 'f', info);
		gettimeofday(info->timer[data->id], NULL);
		print_status(data->id, 'e', info);
		usleep(info->tte * 1000);
		pthread_mutex_unlock(info->locks[data->id]);
		pthread_mutex_unlock(info->locks[data->right_fork]);
	}
}

void	init_philo(t_philos *info, t_personal *data)
{
	static int	num = 1;

	pthread_mutex_lock(info->locks[0]);
	data->times_eaten = 0;
	data->id = num++;
	if (data->id == 1)
		data->right_fork = info->philo_count;
	else
		data->right_fork = data->id - 1;
	pthread_mutex_unlock(info->locks[0]);
	return ;
}

void	*philo(void *philos)
{
	t_philos	*info;
	t_personal	data;

	info = (t_philos *)philos;
	init_philo(info, &data);
	if (data.id % 2 == 1)
		usleep(500);
	while (info->stop == 0 && data.times_eaten != info->meal_count && info->philo_count > 1)
	{
		eating(info, &data);
		data.times_eaten++;
		if (data.times_eaten == info->meal_count)
			set_ready(info);
		print_status(data.id, 's', info);
		usleep(info->tts * 1000);
		print_status(data.id, 't', info);
	}
	return (NULL);
}

void	*watcher(void *philos)
{
	int				i;
	t_philos		*info;
	struct timeval	time;

	info = (t_philos *)philos;
	while (info->stop == 0)
	{
		if (info->ready == info->philo_count)
			set_stop(info);
		gettimeofday(&time, NULL);
		i = 1;
		while (i <= info->philo_count && info->stop == 0)
		{
			if (((time.tv_sec - info->timer[i]->tv_sec) * 1000 + \
					(time.tv_usec - info->timer[i]->tv_usec) / 1000) \
					>= info->ttd)
			{
				print_status(i, 'd', info);
				set_stop(info);
			}
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philos		philos;
	pthread_t		**philo_id;
	int				i;

	if (argc > 6 || argc < 5)
		return (error_handler("Wrong number of arguments!\n"));
	check_input(argv);
	if (populate_struct(&philos, argv) == -1)
		return (error_handler("Invalid values in arguments!\n"));
	if (init_locks(&philos) == -1)
		return (error_handler("Failed to initialize mutex\n"));
	philo_id = init_threads(&philos);
	if (philo_id == NULL)
		return (error_handler("Malloc fail!\n"));
	if (init_timers(&philos) == -1)
		return (error_handler("Malloc fail!\n"));
	if (create_threads(&philos, philo_id) == -1)
		return (error_handler("Failed to create thread!\n"));
	i = 0;
	while (i <= philos.philo_count)
		pthread_join(*philo_id[i++], NULL);
	free_array((void **)philo_id, philos.philo_count + 1);
	free_array((void **)philos.locks, philos.philo_count + 1);
	free_array((void **)philos.timer, philos.philo_count + 1);
}
