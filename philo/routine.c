/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:23:33 by mkiflema          #+#    #+#             */
/*   Updated: 2023/09/10 00:56:52 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo, t_philo *phil)
{
	pthread_mutex_lock(&philo->data->endgame);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->endgame);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->endgame);
	display_log_message(philo, phil->id, GREEN, "is eating😋");
	pthread_mutex_lock(&philo->data->last_eat_locker);
	phil->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->data->last_eat_locker);
	pthread_mutex_lock(&philo->data->eating_times_locker);
	phil->count_eating_times++;
	pthread_mutex_unlock(&philo->data->eating_times_locker);
	waiting_time(philo->data->time_to_eat);
	return (1);
}

int	sleeping(t_philo *philo, t_philo phi)
{
	pthread_mutex_lock(&philo->data->endgame);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->endgame);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->endgame);
	display_log_message(philo, phi.left, YELLOW, "is sleeping😴");
	waiting_time(philo->data->time_to_sleep);
	return (1);
}

int	pick_up_one_fork(t_philo *philo, t_philo phil)
{
	display_log_message(philo, phil.id, BLUE, "is thinking🤔");
	pthread_mutex_lock(&philo->data->endgame);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->endgame);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->endgame);
	if (philo->data->forks[phil.left] == 0)
	{
		pthread_mutex_lock(&philo->data->fork_locker[phil.left]);
		philo->data->forks[phil.left] = phil.id;
		display_log_message(philo, phil.left,
			RESET_COLOR, "has taken a fork");
		pthread_mutex_unlock(&philo->data->fork_locker[phil.left]);
		waiting_time(philo->data->time_to_die);
		return (0);
	}
	return (0);
}

void	*routine(void *phi)
{
	t_philo		*philo;

	philo = (t_philo *)phi;
	if ((philo->id + 1) % 2 == 0)
		usleep(500);
	pthread_mutex_lock(&philo->data->endgame);
	while (philo->data->dead == 0)
	{
		pthread_mutex_unlock(&philo->data->endgame);
		if (philo->data->philo_num == 1 
			&& !pick_up_one_fork(philo, philo->data->philo[philo->id]))
			return ((void *)1);
		else if (!pick_up_multiple_forks(philo, philo->data->philo[philo->id]))
			return ((void *)1);
		if (!eating(philo, &philo->data->philo[philo->id]))
			return ((void *)1);
		if (!put_down_fork(philo, philo->data->philo[philo->id]))
			return ((void *)1);
		if (!sleeping(philo, philo->data->philo[philo->id]))
			return ((void *)1);
		pthread_mutex_lock(&philo->data->endgame);
	}
	pthread_mutex_unlock(&philo->data->endgame);
	return (NULL);
}
