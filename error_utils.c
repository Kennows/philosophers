/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinone <mheinone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:19:14 by mheinone          #+#    #+#             */
/*   Updated: 2025/01/25 17:21:37 by mheinone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] > '9' || argv[i][j] < '0') && argv[i][j] != ' ' \
					&& argv[i][j] != '-' && j <= 11)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void	free_array(void **arr, int nbr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (i < nbr)
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		i++;
	}
	if (arr != NULL)
	{	
		free(arr);
		arr = NULL;
	}
}

int	error_handler(char *err)
{
	int	len;

	len = 0;
	while (err[len])
		len++;
	write(2, "Error: ", 7);
	write(2, err, len);
	return (1);
}

void	free_all(t_philos *info, pthread_t **philo_id)
{
	free_array((void **)philo_id, info->philo_count + 1);
	free_array((void **)info->locks, info->philo_count);
	free_array((void **)info->timer, info->philo_count + 1);
	if (info->init)
		free(info->init);
	if (info->write)
		free(info->write);
	if (info->check)
		free(info->check);
}

void	clean_up(t_philos *info, pthread_t **philo_id, int lvl)
{
	int	i;

	i = 0;
	if (lvl > 1)
	{
		while (i < info->philo_count)
			pthread_mutex_destroy(info->locks[i++]);
		pthread_mutex_destroy(info->init);
		pthread_mutex_destroy(info->write);
		pthread_mutex_destroy(info->check);
	}
	free_all(info, philo_id);
}
