/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:23:33 by mkiflema          #+#    #+#             */
/*   Updated: 2023/06/17 21:24:05 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	display_message(t_info *info, int i, char *color, char *str)
{
	pthread_mutex_lock(&info->print);
	printf("%s%lld Philo %d %s\n%s"RESET_COLOR, color,
		get_time() - info->start_time, i + 1, str, RESET_COLOR);
	pthread_mutex_unlock(&info->print);
}

int	pick_up_fork(t_info *info, int i)
{
	while (is_someone_died(info) == 0)
	{
		pthread_mutex_lock(&info->clear);
		if (info->forks[info->philo[i].left] == 0
			&& info->forks[info->philo[i].right] == 0)
		{
			pthread_mutex_lock(&info->fork_locker[info->philo[i].left]);
			info->forks[info->philo[i].left] = 1;
			pthread_mutex_unlock(&info->fork_locker[info->philo[i].left]);
			display_message(info, info->philo[i].left, RESET_COLOR,
				"has taken a left fork🥄");
			pthread_mutex_lock(&info->fork_locker[info->philo[i].right]);
			info->forks[info->philo[i].right] = 1;
			pthread_mutex_unlock(&info->fork_locker[info->philo[i].right]);
			display_message(info, info->philo[i].left, RESET_COLOR,
				"has taken a right fork🥄");
			pthread_mutex_unlock(&info->clear);
			return (1);
		}
		else
			pthread_mutex_unlock(&info->clear);
	}
	return (0);
}


int	eating(t_info *info, int i)
{
	if (is_someone_died(info))
		return (0);
	display_message(info, info->philo[i].left, GREEN, "is eating😋");
	pthread_mutex_lock(&info->last_eat_locker[i]);
	info->philo[i].last_eat_time = get_time();
	info->philo[i].count_eating_times++;
	pthread_mutex_unlock(&info->last_eat_locker[i]);
	waiting_time(info->time_to_eat);
	return (1);
}

int	put_down_fork(t_info *info, int i)
{
	while (is_someone_died(info) == 0)
	{
		pthread_mutex_lock(&info->clear);
		if (info->forks[info->philo[i].left] == 1
			&& info->forks[info->philo[i].right] == 1)
		{
			pthread_mutex_lock(&info->fork_locker[info->philo[i].right]);
			info->forks[info->philo[i].right] = 0;
			pthread_mutex_unlock(&info->fork_locker[info->philo[i].right]);
			display_message(info, info->philo[i].left, RESET_COLOR,
				"has released a right fork🥄");
			pthread_mutex_lock(&info->fork_locker[info->philo[i].left]);
			info->forks[info->philo[i].left] = 0;
			pthread_mutex_unlock(&info->fork_locker[info->philo[i].left]);
			display_message(info, info->philo[i].left, RESET_COLOR,
				"has released a left fork🥄");
			pthread_mutex_unlock(&info->clear);
			return (1);
		}
		else
			pthread_mutex_unlock(&info->clear);
	}
	return (0);
}

int	sleeping(t_info *info, int i)
{
	if (is_someone_died(info))
		return (0);
	display_message(info, i, YELLOW, "is sleeping😴");
	waiting_time(info->time_to_sleep);
	return (1);
}


void	pick_up_one_fork(t_info *info, int i)
{
	while (is_someone_died(info) == 0)
	{
		if (info->forks[info->philo[i].left] == 0)
		{
			pthread_mutex_lock(&info->fork_locker[info->philo[i].left]);
			info->forks[info->philo[i].left] = 1;
			pthread_mutex_unlock(&info->fork_locker[info->philo[i].left]);
			display_message(info, info->philo[i].left,
				RESET_COLOR, "has taken a fork");
			break ;
		}
	}
}

void	*routine(void *info)
{
	t_info		*inf;
	int			i;

	inf = (t_info *)info;
	pthread_mutex_lock(&inf->thread);
	i = inf->n_thread;
	pthread_mutex_unlock(&inf->thread);
	// if (inf->time_to_die < 60)
	// {
	// 	printf("Error!\n Eating time should be at least 60 ms");
	// 	pthread_mutex_lock(&inf->endgame);
	// 	inf->dead = 1;
	// 	pthread_mutex_unlock(&inf->endgame);
	// 	return (void *)1;
	// }
	while (is_someone_died(info) == 0)
	{
		if (inf->philo_num == 1)
			pick_up_one_fork(inf, i);
		else
			if (!pick_up_fork(inf, i))
				return ((void *)1);
		if (!eating(inf, i))
			return ((void *)1);
		if (!put_down_fork(inf, i))
			return ((void *)1);
		if (!sleeping(inf, i))
			return ((void *)1);
		if (is_someone_died(info))
			return ((void *)1);
		display_message(inf, i, BLUE, "is thinking🤔");
	}
	return (NULL);
}
