/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:23:33 by mkiflema          #+#    #+#             */
/*   Updated: 2023/06/01 22:08:31 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
void static display_mesg(t_info *info, int i, char *str)
{
	pthread_mutex_lock(&info->print);
	if (info->dead == 0)
		printf(" %lld Philo %d %s\n", get_time() - info->start_time, i + 1, str);
	// else if (!strcmp("is died", str))
	// 	printf(" %lld Philo %d %s\n", get_time() - info->start_time, i + 1, str);
	pthread_mutex_unlock(&info->print);
}


void	pick_up_even(t_info *info, int i)
{
	while (info->dead == 0)
	{
		if (info->forks[info->philo[i].left] == 0 && info->forks[info->philo[i].right] == 0)
		{
			pthread_mutex_lock(&info->fork_locker[info->philo[i].right]);
			pthread_mutex_lock(&info->fork_locker[info->philo[i].left]);
			info->forks[info->philo[i].left] = 1;
			info->forks[info->philo[i].right] = 1;
			display_mesg(info, info->philo[i].left, "has taken the forks");
			display_mesg(info, info->philo[i].left, "is eating");
			info->philo[i].last_eat_time = get_time();
			wating_time(info->time_to_eat);
			break;
		}
	}
}

void	pick_up_fork(t_info *info, int i)
{
	if (i % 2 == 0)
		pick_up_even(info, i);
	else 
	{
		while (info->dead == 0)
		{
			if (info->forks[info->philo[i].left] == 0 && info->forks[info->philo[i].right] == 0)
			{
				pthread_mutex_lock(&info->fork_locker[info->philo[i].left]);
				pthread_mutex_lock(&info->fork_locker[info->philo[i].right]);
				info->forks[info->philo[i].left] = 1;
				info->forks[info->philo[i].right] = 1;
				display_mesg(info, info->philo[i].left, "has taken the forks");
				display_mesg(info, info->philo[i].left, "is eating");
				info->philo[i].last_eat_time = get_time();
				wating_time(info->time_to_eat);
				break;
			}
		}
	}
}


void	put_down_fork(t_info *info, int i)
{

	while (info->dead == 0)
	{
		if (info->forks[info->philo[i].left] == 1 && info->forks[info->philo[i].right] == 1)
		{
			info->forks[info->philo[i].left] = 0;
			info->forks[info->philo[i].right] = 0;
			pthread_mutex_unlock(&info->fork_locker[info->philo[i].left]);
			pthread_mutex_unlock(&info->fork_locker[info->philo[i].right]);
			display_mesg(info, info->philo[i].left, "has released the forks");
			break;
		}
	}
}

void	sleeping(t_info *info, int i)
{
		display_mesg(info, i, "is sleeping😴");
		wating_time(info->time_to_sleep);
}

// void	thinking(t_info *info, int i)
// {
// 	printf(" %lld Philo %d is thinking🤔\n", get_time() - info->start_time, i + 1);
// }

void	*routine(void *info)
{
	t_info		*inf;
	int			i;

	inf = (t_info *)info;
	i =  inf->n_thread;
	while (inf->dead == 0)
	{
		pick_up_fork(inf, i);
		put_down_fork(inf, i);
		sleeping(inf, i);
		display_mesg(inf, i, "is thinking🤔");
	}
	// if (inf->dead == 1 && inf->flag)
	// {
	// 	printf(" %lld Philo %d is dead\n", get_time() - inf->start_time, i + 1);
	// 	inf->flag = 0;
	// 	return (FALSE);
	// }
	return (NULL);
}
