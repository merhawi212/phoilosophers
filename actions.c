/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:46:41 by mkiflema          #+#    #+#             */
/*   Updated: 2023/08/19 22:41:11 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_up_fork_even(t_info *info, int i)
{
	pthread_mutex_lock(&info->fork_locker[info->philo[i].right]);
	pthread_mutex_lock(&info->fork_locker[info->philo[i].left]);
	while ((info->forks[info->philo[i].left]
			|| info->forks[info->philo[i].right]))
	{
		pthread_mutex_unlock(&info->fork_locker[info->philo[i].right]);
		pthread_mutex_unlock(&info->fork_locker[info->philo[i].left]);
		pthread_mutex_lock(&info->isdead);
		if (info->dead)
		{
			pthread_mutex_unlock(&info->isdead);
			return (0);
		}
		pthread_mutex_unlock(&info->isdead);
		usleep(100);
		pthread_mutex_lock(&info->fork_locker[info->philo[i].right]);
		pthread_mutex_lock(&info->fork_locker[info->philo[i].left]);
	}
	info->forks[info->philo[i].left] = 1;
	display_message(info, info->philo[i].left, RESET_COLOR,
		"has taken a left fork🥄");
	info->forks[info->philo[i].right] = 1;
	display_message(info, info->philo[i].left, RESET_COLOR,
		"has taken a right fork🥄");
	pthread_mutex_unlock(&info->fork_locker[info->philo[i].right]);
	pthread_mutex_unlock(&info->fork_locker[info->philo[i].left]);
	return (1);
}

int	pick_up_fork(t_info *info, int i)
{
	pthread_mutex_lock(&info->fork_locker[info->philo[i].left]);
	pthread_mutex_lock(&info->fork_locker[info->philo[i].right]);
	while ((info->forks[info->philo[i].left]
			|| info->forks[info->philo[i].right]))
	{
		pthread_mutex_unlock(&info->fork_locker[info->philo[i].left]);
		pthread_mutex_unlock(&info->fork_locker[info->philo[i].right]);
		pthread_mutex_lock(&info->isdead);
		if (info->dead)
		{
			pthread_mutex_unlock(&info->isdead);
			return (0);
		}
		pthread_mutex_unlock(&info->isdead);
		usleep(100);
		pthread_mutex_lock(&info->fork_locker[info->philo[i].left]);
		pthread_mutex_lock(&info->fork_locker[info->philo[i].right]);
	}
	info->forks[info->philo[i].left] = 1;
	display_message(info, info->philo[i].left, RESET_COLOR,
		"has taken a left fork🥄");
	info->forks[info->philo[i].right] = 1;
	display_message(info, info->philo[i].left, RESET_COLOR,
		"has taken a right fork🥄");
	pthread_mutex_unlock(&info->fork_locker[info->philo[i].left]);
	pthread_mutex_unlock(&info->fork_locker[info->philo[i].right]);
	return (1);
}
// int	pick_up_fork(t_info *info, int i)
// {
// 	// pthread_mutex_lock(&info->endgame);
// 	while (info->dead == 0)
// 	{
// 		// pthread_mutex_unlock(&info->endgame);
// 		// pthread_mutex_unlock(&info->fork_locker[info->philo[i].left]);
// 		// pthread_mutex_unlock(&info->fork_locker[info->philo[i].right]);
// 		if ((info->forks[info->philo[i].left]
// 				&& info->forks[info->philo[i].right]))
// 		{
// 			pthread_mutex_lock(&info->fork_locker[info->philo[i].left]);
// 			pthread_mutex_lock(&info->fork_locker[info->philo[i].right]);
// 			info->forks[info->philo[i].left] = 1;
// 			display_message(info, info->philo[i].left, RESET_COLOR,
// 				"has taken a left fork🥄");
// 			info->forks[info->philo[i].right] = 1;
// 			display_message(info, info->philo[i].left, RESET_COLOR,
// 				"has taken a right fork🥄");
// 			pthread_mutex_unlock(&info->fork_locker[info->philo[i].left]);
// 			pthread_mutex_unlock(&info->fork_locker[info->philo[i].right]);
// 			return (1);
// 		}
// 		// pthread_mutex_lock(&info->endgame);
// 		usleep(100);
// 	}
// 	// pthread_mutex_unlock(&info->endgame);
// 	return (0);
// }

int	eating(t_info *info, int i)
{
	// pthread_mutex_lock(&info->endgame);
	if (info->dead)
	{
		// pthread_mutex_unlock(&info->endgame);
		return (0);
	}
	display_message(info, info->philo[i].left, GREEN, "is eating😋");
	pthread_mutex_lock(&info->last_eat_locker);
	info->philo[i].last_eat_time = get_time();
	info->philo[i].count_eating_times++;
	pthread_mutex_unlock(&info->last_eat_locker);
	waiting_time(info->time_to_eat);
	// pthread_mutex_unlock(&info->endgame);
	return (1);
}

int	put_down_fork(t_info *info, int i)
{
	pthread_mutex_lock(&info->fork_locker[info->philo[i].right]);
	pthread_mutex_lock(&info->fork_locker[info->philo[i].left]);
	info->forks[info->philo[i].right] = 0;
	info->forks[info->philo[i].left] = 0;
	display_message(info, info->philo[i].left, RESET_COLOR,
		"has released a right fork🥄");
	display_message(info, info->philo[i].left, RESET_COLOR,
		"has released a left fork🥄");
	pthread_mutex_unlock(&info->fork_locker[info->philo[i].left]);
	pthread_mutex_unlock(&info->fork_locker[info->philo[i].right]);
	return (1);
}

int	sleeping(t_info *info, int i)
{
	pthread_mutex_lock(&info->endgame);
	if (info->dead)
	{
		pthread_mutex_unlock(&info->endgame);
		return (0);
	}
	pthread_mutex_unlock(&info->endgame);
	display_message(info, i, YELLOW, "is sleeping😴");
	waiting_time(info->time_to_sleep);
	return (1);
}
