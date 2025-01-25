/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialazation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinone <mheinone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:03:58 by mheinone          #+#    #+#             */
/*   Updated: 2025/01/25 18:46:37 by mheinone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	malloc_locks(t_philos *philos)
{
	int	i;

	i = 0;
	philos->write = malloc(sizeof(pthread_mutex_t));
	philos->check = malloc(sizeof(pthread_mutex_t));
	philos->init = malloc(sizeof(pthread_mutex_t));
	philos->locks = malloc((philos->philo_count) \
		* sizeof(pthread_mutex_t *));
	if (philos->locks == NULL || philos->write == NULL || \
		philos->init == NULL || philos->check == NULL)
		return (-1);
	while (i < philos->philo_count)
	{
		philos->locks[i] = malloc(sizeof (pthread_mutex_t));
		if (philos->locks[i] == NULL)
		{
			free_array((void **)philos->locks, i);
			return (-1);
		}
		i++;
	}
	return (1);
}

int	init_locks(t_philos *philos)
{
	int	i;

	i = 0;
	if (malloc_locks(philos) == -1)
		return (-1);
	if (pthread_mutex_init(philos->write, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(philos->check, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(philos->init, NULL) != 0)
		return (-1);
	while (i < philos->philo_count)
	{
		if (pthread_mutex_init(philos->locks[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (1);
}

int	init_timers(t_philos *philos)
{
	int				i;
	long			time;

	philos->timer = malloc(sizeof (long) \
			* (philos->philo_count + 1));
	if (philos->timer == NULL)
		return (-1);
	i = 0;
	time = get_time();
	while (i <= philos->philo_count)
	{
		philos->timer[i] = malloc(sizeof (long));
		if (philos->timer[i] == NULL)
		{
			free_array((void **)philos->timer, i);
			return (-1);
		}
		if (i == 0)
			*philos->timer[i++] = time;
		else
			*philos->timer[i++] = 0;
	}
	return (1);
}

int	create_threads(t_philos *philos, pthread_t **philo_id)
{
	int	i;

	i = 1;
	while (i <= philos->philo_count)
	{
		if (pthread_create(philo_id[i], NULL, *(philo), philos) != 0)
		{
			check_stop(philos, SET);
			return (-1);
		}
		i++;
	}
	if (pthread_create(philo_id[0], NULL, *(watcher), philos) != 0)
	{
		check_stop(philos, SET);
		return (-1);
	}
	return (1);
}

pthread_t	**init_threads(t_philos *philos)
{
	int			i;
	pthread_t	**philo_id;

	i = 0;
	philo_id = malloc(sizeof (pthread_t *) * (philos->philo_count + 1));
	if (philo_id == NULL)
		return (NULL);
	while (i <= philos->philo_count)
	{
		philo_id[i] = malloc(sizeof (pthread_t));
		if (philo_id[i] == NULL)
		{
			free_array((void **)philo_id, i);
			return (NULL);
		}
		i++;
	}
	return (philo_id);
}
