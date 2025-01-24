/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinone <mheinone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:45:01 by mheinone          #+#    #+#             */
/*   Updated: 2025/01/24 21:02:24 by mheinone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philos *info, t_personal *data)
{
	if (data->id % 2 == 0)
	{
		pthread_mutex_lock(info->locks[data->left_fork]);
		print_status(data->id, 'f', info);
		pthread_mutex_lock(info->locks[data->right_fork]);
		print_status(data->id, 'f', info);
	}
	else
	{
		pthread_mutex_lock(info->locks[data->right_fork]);
		print_status(data->id, 'f', info);
		pthread_mutex_lock(info->locks[data->left_fork]);
		print_status(data->id, 'f', info);
	}
	check_time(info, SET, data->id);
	print_status(data->id, 'e', info);
	ft_sleep(info, info->tte);
	pthread_mutex_unlock(info->locks[data->left_fork]);
	pthread_mutex_unlock(info->locks[data->right_fork]);
}

void	init_philo(t_philos *info, t_personal *data)
{
	static int	num = 1;

	pthread_mutex_lock(info->init);
	data->times_eaten = 0;
	data->id = num++;
	data->right_fork = data->id - 1;
	if (data->id == info->philo_count)
		data->left_fork = 0;
	else
		data->left_fork = data->id;
	pthread_mutex_unlock(info->init);
	if (data->id % 2 != 0)
	{
		print_status(data->id, 't', info);
		usleep(info->tte * 500);
	}
	return ;
}

void	*philo(void *philos)
{
	t_philos	*info;
	t_personal	data;

	info = (t_philos *)philos;
	init_philo(info, &data);
	while (check_stop(info, CHECK) == 0 && data.times_eaten != info->meal_count)
	{
		if (info->philo_count == 1)
		{
			pthread_mutex_lock(info->locks[data.right_fork]);
			print_status(data.id, 'f', info);
			usleep(info->ttd * 1000);
			pthread_mutex_unlock(info->locks[data.right_fork]);
			return (NULL);
		}
		eating(info, &data);
		data.times_eaten++;
		if (data.times_eaten == info->meal_count)
			check_ready(info, SET);
		print_status(data.id, 's', info);
		ft_sleep(info, info->tts);
		print_status(data.id, 't', info);
	}
	return (NULL);
}

void	*watcher(void *philos)
{
	int				i;
	t_philos		*info;
	long			time;

	info = (t_philos *)philos;
	while (check_stop(info, CHECK) == 0)
	{
		if (check_ready(info, CHECK) == 1)
			check_stop(info, SET);
		i = 1;
		time = check_time(info, CHECK, 0);
		while (i <= info->philo_count && check_stop(info, CHECK) == 0)
		{
			if (time - check_time(info, CHECK, i) >= info->ttd)
			{
				print_status(i, 'd', info);
				check_stop(info, SET);
			}
			i++;
		}
		usleep(100);
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
	clean_up(&philos, philo_id);
}
