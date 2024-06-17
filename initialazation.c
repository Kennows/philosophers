/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialazation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinone <mheinone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:03:58 by mheinone          #+#    #+#             */
/*   Updated: 2024/06/17 15:28:51 by mheinone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_locks(t_philos *philos)
{
	int	i;

	i = 0;
	philos->locks = malloc((philos->philo_count + 1) \
		* sizeof(pthread_mutex_t *));
	if (philos->locks == NULL)
		return (-1);
	while (i <= philos->philo_count)
	{
		philos->locks[i] = malloc(sizeof (pthread_mutex_t));
		if (philos->locks[i] == NULL)
		{
			while (--i >= 0)
				free(philos->locks[i]);
			free(philos->locks);
			return (-1);
		}
		pthread_mutex_init(philos->locks[i], NULL);
		i++;
	}
	return (1);
}

int	init_timers(t_philos *philos)
{
	int	i;

	philos->timer = malloc(sizeof (struct timeval *) \
			* (philos->philo_count + 1));
	if (philos->timer == NULL)
		return (-1);
	i = 0;
	while (i <= philos->philo_count)
	{
		philos->timer[i] = malloc(sizeof (struct timeval));
		if (philos->timer[i] == NULL)
		{
			while (--i >= 0)
				free(philos->timer[i]);
			free(philos->timer);
			return (-1);
		}
		gettimeofday(philos->timer[i], NULL);
		i++;
	}
	return (1);
}

int	populate_struct(t_philos *philos, char **argv)
{
	philos->philo_count = ft_atol(argv[1]);
	if (philos->philo_count < 1 || philos->philo_count > 2147483647)
		return (-1);
	philos->ttd = ft_atol(argv[2]);
	if (philos->ttd < 0 || philos->ttd > 2147483647)
		return (-1);
	philos->tte = ft_atol(argv[3]);
	if (philos->tte < 0 || philos->tte > 2147483647)
		return (-1);
	philos->tts = ft_atol(argv[4]);
	if (philos->tts < 0 || philos->tts > 2147483647)
		return (-1);
	if (argv[5] == NULL)
		philos->meal_count = -1;
	else
		philos->meal_count = ft_atol(argv[5]);
	if (philos->meal_count < -1 || philos->meal_count > 2147483647)
		return (-1);
	philos->stop = 0;
	philos->ready = 0;
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
			philos->stop = 1;
			return (-1);
		}
		i++;
	}
	if (pthread_create(philo_id[0], NULL, *(watcher), philos) != 0)
	{
		philos->stop = 1;
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
			while (--i >= 0)
				free(philo_id[i]);
			free(philo_id);
			return (NULL);
		}
		i++;
	}
	return (philo_id);
}
