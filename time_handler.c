/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:27:02 by mkiflema          #+#    #+#             */
/*   Updated: 2023/05/27 13:37:44 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	is_dead(t_info *info)
{
	long long	elapsed_time;

	if (info->time_to_die > 0) 
	{
		elapsed_time = get_time() - info->philo->last_eat_time;
		// printf("currenttime %lli: lasttime %lli\n", get_time(), info->philo->last_eat_time);
		if (elapsed_time < info->time_to_die)
			return (1);
		else
		{
			info->dead = 1;
			return (0);
		}
	}
	info->dead = 1;
	return (0);
}

void	wating_time(int	time)
{
	usleep(1000 * time);
}