/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinone <mheinone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:45:09 by mheinone          #+#    #+#             */
/*   Updated: 2024/06/17 15:44:54 by mheinone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philos
{
	int				philo_count;
	int				ttd;
	int				tte;
	int				tts;
	int				meal_count;
	int				ready;
	struct timeval	**timer;
	pthread_mutex_t	**locks;
	int				stop;

}	t_philos;

typedef struct s_personal
{
	int	times_eaten;
	int	id;
	int	right_fork;
}	t_personal;

void		check_input(char **argv);
int			error_handler(char *err);
void		free_array(void **arr, int nbr);
long		ft_atol(char *str);
int			populate_struct(t_philos *philos, char **argv);
int			init_locks(t_philos *philos);
int			init_timers(t_philos *philos);
pthread_t	**init_threads(t_philos *philos);
int			create_threads(t_philos *philos, pthread_t **philo_id);
void		*philo(void *philos);
void		*watcher(void *philos);
void		print_status(int philo, char action, t_philos *info);
void		set_stop(t_philos *info);
void		set_ready(t_philos *info);

#endif
