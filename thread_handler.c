/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:31:45 by mkiflema          #+#    #+#             */
/*   Updated: 2023/05/27 12:53:56 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_thread(t_info *info)
{
	int	i;

	info->p_th = malloc(sizeof(pthread_t) * info->philo_num + 1);
	if (!info->p_th)
		return (FALSE);
	i = -1;
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
	i = -1;
	while (++i < info->philo_num)
		pthread_join(info->p_th[i], NULL);
	return (TRUE);
}