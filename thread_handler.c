/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:31:45 by mkiflema          #+#    #+#             */
/*   Updated: 2023/08/26 15:29:56 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_thread(t_info *info)
{
	int	i;

	i = -1;
	info->start_time = get_time();
	while (++i < info->philo_num)
	{
		if (is_someone_died(&info->philo[i]) == 0)
		{
			if (pthread_create(&info->philo[i].p_thread, NULL,
					&routine, (void *)&info->philo[i]) != 0)
			{
				return (0);
			}
		}
		else
			return (FALSE);
		usleep(1000);
	}
	if (!checker(info))
		return (FALSE);
	// if (!thread_join(info))
	// 	return (FALSE);
	return (TRUE);
}
