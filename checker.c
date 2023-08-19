/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:56:39 by mkiflema          #+#    #+#             */
/*   Updated: 2023/08/19 22:36:27 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_info *info)
{
	long long	elapsed_time;
	int			i;

	i = -1;
	while (++i < info->philo_num)
	{
		pthread_mutex_lock(&info->last_eat_locker);
		elapsed_time = get_time() - info->philo[i].last_eat_time;
		if (elapsed_time >= info->time_to_die)
		{
			pthread_mutex_unlock(&info->last_eat_locker);
			pthread_mutex_lock(&info->endgame);
			info->dead = 1;
			pthread_mutex_unlock(&info->endgame);
			printf(RED" %lld Philo %d is dead\n"RESET_COLOR,
				get_time() - info->start_time, i + 1);
			return (0);
		}
		pthread_mutex_unlock(&info->last_eat_locker);
	}
	return (1);
}

int	check_eating_times(t_info *info)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < info->philo_num)
		sum += info->philo[i++].count_eating_times;
	if (sum >= (info->times_must_eat * info->philo_num))
	{
		pthread_mutex_lock(&info->endgame);
		info->dead = 1;
		printf("%lld game ended🔚\n", get_time() - info->start_time);
		pthread_mutex_unlock(&info->endgame);
		return (0);
	}
	return (1);
}

int	is_someone_died(t_info *info)
{
	int	res;

	pthread_mutex_lock(&info->isdead);
	res = info->dead;
	pthread_mutex_unlock(&info->isdead);
	return (res);
}

int	checker(t_info *info)
{
	while (1)
	{
		if (!is_dead(info))
			return (0);
		if (info->times_must_eat >= 1)
			if (!check_eating_times(info))
				return (0);
	}
	return (0);
}
