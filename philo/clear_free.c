/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:53:11 by mkiflema          #+#    #+#             */
/*   Updated: 2023/09/02 14:56:38 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_join(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		pthread_join(data->philo[i].p_thread, NULL);
	return (TRUE);
}

void	destroy_mutexes(t_data *data)
{
	pthread_mutex_destroy(&data->last_eat_locker);
	pthread_mutex_destroy(&data->endgame);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->eating_times_locker);
}

void	destroy_free_fork(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		pthread_mutex_destroy(&data->fork_locker[i]);
	free(data->fork_locker);
	free(data->forks);
}

void	clear_all(t_data *data)
{
	destroy_mutexes(data);
	destroy_free_fork(data);
	free(data->philo);
	free(data);
	return ;
}
