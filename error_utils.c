/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinone <mheinone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:19:14 by mheinone          #+#    #+#             */
/*   Updated: 2024/05/31 14:32:23 by mheinone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_input(char **argv)
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
					&& argv[i][j] != '-')
				error_handler("Non-numeric character\n");
			if (j > 11)
				error_handler("Value exceeds integer limits!\n");
			j++;
		}
		i++;
	}
}

void	free_array(void **arr, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		i++;
	}
	free(arr);
	arr = NULL;
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
