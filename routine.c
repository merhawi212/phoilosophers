/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:23:33 by mkiflema          #+#    #+#             */
/*   Updated: 2023/05/27 13:27:18 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_fork(t_info *info, int i)
{
	int	left;
	int	right;

	left = i;
	right = (i + 1) % info->philo_num;
	while (info->dead == 0)
	{
		if (info->forks[left] == 0 && info->forks[right] == 0)
		{
			pthread_mutex_lock(&info->fork_locker[left]);
			pthread_mutex_lock(&info->fork_locker[right]);
			info->forks[left] = 1;
			info->forks[right] = 1;
			printf("Philo %d has taken fork %d (left)"
			"and %d (right)\n", i + 1, left + 1, right + 1);
			printf("Philo %d is eating😋\n", i + 1);
			wating_time(info->time_to_sleep);
			break;
		}
	}
}

void	put_down_fork(t_info *info, int i)
{
	int	left;
	int	right;

	left = i;
	right = (i + 1) % info->philo_num;
	while (info->dead == 0)
	{
		if (info->forks[left] == 1 && info->forks[right] == 1)
		{
			info->forks[left] = 0;
			info->forks[right] = 0;
			info->philo[i].last_eat_time = get_time();
			pthread_mutex_unlock(&info->fork_locker[left]);
			printf("Philo %d has released fork %d and %d \n", i + 1, left + 1, right + 1);
			pthread_mutex_unlock(&info->fork_locker[right]);
			break;
		}
	}
}

void	sleeping(t_info *info, int i)
{
	printf("Philo %d is sleeping😴\n", i + 1);
	wating_time(info->time_to_sleep);
}

void	thinking(t_info *info, int i)
{
	printf("Philo %d is thinking🤔\n", i + 1);
}

void	*routine(void *info)
{
	t_info		*inf;
	int			i;

	inf = (t_info *)info;
	i =  inf->n_thread;
	while (is_dead(inf) && inf->dead == 0)
	{
		pick_up_fork(inf, i);
		put_down_fork(inf, i);
		sleeping(inf, i);
		thinking(inf, i);
	}
	if (inf->dead == 1)
	{
		printf("Philo %d is died💀\n", i + 1);
		return (FALSE);
	}
	return (NULL);
}
