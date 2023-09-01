/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:56:39 by mkiflema          #+#    #+#             */
/*   Updated: 2023/08/31 21:26:36 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_data *data)
{
	long long	elapsed_time;
	int			i;

	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_lock(&data->last_eat_locker);
		elapsed_time = get_time() - data->philo[i].last_eat_time;
		if (elapsed_time >= data->time_to_die)
		{
			pthread_mutex_unlock(&data->last_eat_locker);
			pthread_mutex_lock(&data->endgame);
			data->dead = 1;
			pthread_mutex_unlock(&data->endgame);
			display_log_message(&data->philo[i], i, RED, " dead");
			return (0);
		}
		pthread_mutex_unlock(&data->last_eat_locker);
		usleep(100);
	}
	return (1);
}

// printf(CYAN"----Game ended! GG----\n"RESET_COLOR);
int	check_eating_times(t_data *data)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->eating_times_locker);
		sum += data->philo[i++].count_eating_times;
		pthread_mutex_unlock(&data->eating_times_locker);
	}
	if (sum >= (data->times_must_eat * data->philo_num))
	{
		pthread_mutex_lock(&data->endgame);
		data->dead = 1;
		pthread_mutex_unlock(&data->endgame);
		return (0);
	}
	return (1);
}

int	checker(t_data *data)
{
	while (1)
	{
		if (!is_dead(data))
			return (0);
		if (data->times_must_eat >= 1)
			if (!check_eating_times(data))
				return (0);
		usleep(500);
	}
	return (0);
}
