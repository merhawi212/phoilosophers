/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:10:03 by mkiflema          #+#    #+#             */
/*   Updated: 2023/08/26 17:09:27 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_fork(t_info *info)
{
	int	i;

	info->fork_locker = malloc(sizeof(pthread_mutex_t) * info->philo_num);
	if (!info->fork_locker)
		return (FALSE);
	info->forks = malloc(sizeof(int) * info->philo_num);
	if (!info->forks)
		return (FALSE);
	i = -1;
	// info->last_eat_locker = malloc(sizeof(pthread_mutex_t) * info->philo_num);
	// if (!info->last_eat_locker)
	// 	return (FALSE);
	while (++i < info->philo_num)
	{
		info->forks[i] = 0;
		pthread_mutex_init(&info->fork_locker[i], NULL);
	}
	pthread_mutex_init(&info->last_eat_locker, NULL);
	pthread_mutex_init(&info->print, NULL);
	pthread_mutex_init(&info->endgame, NULL);
	return (TRUE);
}
