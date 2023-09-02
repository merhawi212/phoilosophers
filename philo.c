/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:53:59 by mkiflema          #+#    #+#             */
/*   Updated: 2023/09/02 14:54:02 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_fork(t_data *data)
{
	int	i;

	data->fork_locker = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->fork_locker)
		return (FALSE);
	data->forks = malloc(sizeof(int) * data->philo_num);
	if (!data->forks)
		return (free(data->fork_locker), FALSE);
	i = -1;
	while (++i < data->philo_num)
	{
		data->forks[i] = 0;
		pthread_mutex_init(&data->fork_locker[i], NULL);
	}
	return (TRUE);
}

int	create_philos(t_data *data)
{
	long long	current_time;
	int			i;

	data->philo = malloc(sizeof(t_philo) * (data->philo_num + 1));
	if (!data->philo)
		return (FALSE);
	current_time = get_time();
	i = -1;
	while (++i < data->philo_num)
	{
		data->philo[i].id = i;
		data->philo[i].left = i;
		data->philo[i].right = (i + 1) % data->philo_num;
		data->philo[i].last_eat_time = current_time;
		data->philo[i].count_eating_times = 0;
		data->philo[i].data = data;
	}
	return (TRUE);
}

int	create_thread(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->philo_num)
	{
		if (data->dead == 0)
		{
			if (pthread_create(&data->philo[i].p_thread, NULL,
					&routine, (void *)&data->philo[i]) != 0)
				return (0);
		}
		else
			return (FALSE);
		usleep(100);
	}
	if (!checker(data))
		return (FALSE);
	return (TRUE);
}
