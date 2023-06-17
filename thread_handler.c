/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:31:45 by mkiflema          #+#    #+#             */
/*   Updated: 2023/06/17 21:04:15 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int static	thread_join(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
		pthread_join(info->p_th[i], NULL);
	return (TRUE);
}

int	create_thread(t_info *info)
{
	int	i;

	info->p_th = malloc(sizeof(pthread_t) * info->philo_num);
	if (!info->p_th)
		return (FALSE);
	i = -1;
	info->start_time = get_time();
	while (++i < info->philo_num)
	{
		pthread_mutex_lock(&info->thread);
		info->n_thread = i;
		pthread_mutex_unlock(&info->thread);
		if (is_someone_died(info) == 0)
		{
			if (pthread_create(&info->p_th[i], NULL,
					&routine, (void *)info) != 0)
			{
				thread_join(info);
				return (0);
			}
		}
		else
			return (FALSE);
		usleep(1000);
	}
	if (!checker(info))
		return (FALSE);
	if (!thread_join(info))
		return (FALSE);
	return (TRUE);
}
