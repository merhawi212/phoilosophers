/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:23:33 by mkiflema          #+#    #+#             */
/*   Updated: 2023/08/26 18:23:25 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_message(t_philo *philo, int id, char *color, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%s%lld Philo %d %s\n%s"RESET_COLOR, color,
		get_time() - philo->data->start_time, id + 1, str, RESET_COLOR);
	pthread_mutex_unlock(&philo->data->print);
}

int	pick_up_one_fork(t_philo *philo, t_philo phil)
{
	while (is_someone_died(philo) == 0)
	{
		if (philo->data->forks[phil.left] == 0)
		{
			pthread_mutex_lock(&philo->data->fork_locker[phil.left]);
			philo->data->forks[phil.left] = 1;
			display_message(philo, phil.left,
				RESET_COLOR, "has taken a fork");
			pthread_mutex_unlock(&philo->data->fork_locker[phil.left]);
			break ;
		}
	}
	return (0);
}

void	*routine(void *phi)
{
	t_philo		*philo;

	philo = (t_philo *)phi;
	while (is_someone_died(philo) == 0)
	{
		if (philo->data->philo_num == 1 
			&& !pick_up_one_fork(philo, philo->data->philo[philo->id]))
			return ((void *)1);
		else
			if (!pick_up_fork(philo, philo->data->philo[philo->id]))
				return ((void *)1);
		if (!eating(philo, &philo->data->philo[philo->id]))
			return ((void *)1);
		if (!put_down_fork(philo, philo->data->philo[philo->id]))
			return ((void *)1);
		if (!sleeping(philo, philo->data->philo[philo->id]))
			return ((void *)1);
	}
	return (NULL);
}

	// if (inf->time_to_die < 60)
	// {
	// 	printf("Error!\n Eating time should be at least 60 ms");
	// 	pthread_mutex_lock(&inf->endgame);
	// 	inf->dead = 1;
	// 	pthread_mutex_unlock(&inf->endgame);
	// 	return (void *)1;
	// }
	// pthread_mutex_lock(&inf->endgame);