/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinone <mheinone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:24:23 by mheinone          #+#    #+#             */
/*   Updated: 2025/01/25 18:47:28 by mheinone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (philos->meal_count == 0)
		philos->ready = philos->philo_count;
	else
		philos->ready = 0;
	return (1);
}

int	start_up(t_philos *philos, pthread_t **philo_id)
{
	if (init_locks(philos) == -1)
		return (1);
	if (init_timers(philos) == -1)
		return (2);
	if (create_threads(philos, philo_id) == -1)
		return (2);
	return (0);
}
