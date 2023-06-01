/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:31:45 by mkiflema          #+#    #+#             */
/*   Updated: 2023/06/01 22:10:14 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_info *info, int i)
{
	long long	elapsed_time;

	if (info->time_to_die > 60) 
	{
		elapsed_time = get_time() - info->philo[i].last_eat_time;
		if (elapsed_time >= info->time_to_die)
		{
			info->dead = 1;
			printf(" %lld Philo %d is dead\n", get_time() - info->start_time, i + 1);
			return (0);
		}
	}
	else 
		info->dead = 1;
	return (0);
}

int	create_thread(t_info *info)
{
	int	i;

	info->p_th = malloc(sizeof(pthread_t) * info->philo_num + 1);
	if (!info->p_th)
		return (FALSE);
	i = -1;
	info->start_time = get_time();
	while (++i < info->philo_num)
	{
		info->n_thread = i;
		if (info->dead == 0)
		{
			if (pthread_create(&info->p_th[i], NULL, &routine, (void *)info) != 0)
				return (FALSE);
		}
		else
			return (FALSE);
		usleep(1000);
	}
	i = 0;
	while (info->dead == 0)
	{
		is_dead(info, i);
		i++;
		i = i % info->philo_num;
	}
	i = -1;
	while (++i < info->philo_num)
	{
		if (info->dead == 0)
			pthread_join(info->p_th[i], NULL);
		else
			return (FALSE);
	}
	return (TRUE);
}
