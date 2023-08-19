/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:23:33 by mkiflema          #+#    #+#             */
/*   Updated: 2023/08/19 22:38:21 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_message(t_info *info, int i, char *color, char *str)
{
	pthread_mutex_lock(&info->print);
	printf("%s%lld Philo %d %s\n%s"RESET_COLOR, color,
		get_time() - info->start_time, i + 1, str, RESET_COLOR);
	pthread_mutex_unlock(&info->print);
}

int	pick_up_one_fork(t_info *info, int i)
{
	while (is_someone_died(info) == 0)
	{
		if (info->forks[info->philo[i].left] == 0)
		{
			pthread_mutex_lock(&info->fork_locker[info->philo[i].left]);
			info->forks[info->philo[i].left] = 1;
			display_message(info, info->philo[i].left,
				RESET_COLOR, "has taken a fork");
			pthread_mutex_unlock(&info->fork_locker[info->philo[i].left]);
			break ;
		}
	}
	return (0);
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
	// pthread_mutex_lock(&inf->endgame);
	while (inf->dead == 0)
	{
		// pthread_mutex_unlock(&inf->endgame);
		display_message(inf, i, BLUE, "is thinking🤔");
		if (inf->philo_num == 1 && !pick_up_one_fork(inf, i))
			return ((void *)1);
		else
			if (!pick_up_fork(inf, i))
				return ((void *)1);
		if (!eating(inf, i))
			return ((void *)1);
		if (!put_down_fork(inf, i))
			return ((void *)1);
		if (!sleeping(inf, i))
			return ((void *)1);
		if (is_someone_died(inf))
			return ((void *)1);
		// pthread_mutex_lock(&inf->endgame);
	}
	// pthread_mutex_unlock(&inf->endgame);
	return (NULL);
}
