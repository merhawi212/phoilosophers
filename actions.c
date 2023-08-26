/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:46:41 by mkiflema          #+#    #+#             */
/*   Updated: 2023/08/26 19:40:00 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_up_fork_even(t_philo *philo, t_philo phi)
{
	pthread_mutex_lock(&philo->data->fork_locker[phi.right]);
	pthread_mutex_lock(&philo->data->fork_locker[phi.left]);
	while ((philo->data->forks[phi.left]
			|| philo->data->forks[phi.right]))
	{
		pthread_mutex_unlock(&philo->data->fork_locker[phi.right]);
		pthread_mutex_unlock(&philo->data->fork_locker[phi.left]);
		pthread_mutex_lock(&philo->data->endgame);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->endgame);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->endgame);
		usleep(200);
		pthread_mutex_lock(&philo->data->fork_locker[phi.right]);
		pthread_mutex_lock(&philo->data->fork_locker[phi.left]);
	}
	philo->data->forks[phi.left] = 1;
	display_message(philo, phi.left, RESET_COLOR,
		"has taken a left fork🥄");
	philo->data->forks[phi.right] = 1;
	display_message(philo, phi.left, RESET_COLOR,
		"has taken a right fork🥄");
	pthread_mutex_unlock(&philo->data->fork_locker[phi.right]);
	pthread_mutex_unlock(&philo->data->fork_locker[phi.left]);
	return (1);
}

int	pick_up_fork(t_philo *philo, t_philo phi)
{
	display_message(philo, phi.id, BLUE, "is thinking🤔");
	if ((phi.id + 1) % 2 == 0)
	{
		usleep(1500);
		if (!pick_up_fork_even(philo, phi))
			return (0);
		return (1);
	}
	pthread_mutex_lock(&philo->data->fork_locker[phi.left]);
	pthread_mutex_lock(&philo->data->fork_locker[phi.right]);
	while ((philo->data->forks[phi.left]
			|| philo->data->forks[phi.right]))
	{
		pthread_mutex_unlock(&philo->data->fork_locker[phi.left]);
		pthread_mutex_unlock(&philo->data->fork_locker[phi.right]);
		pthread_mutex_lock(&philo->data->endgame);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->endgame);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->endgame);
		usleep(100);
		pthread_mutex_lock(&philo->data->fork_locker[phi.left]);
		pthread_mutex_lock(&philo->data->fork_locker[phi.right]);
	}
	philo->data->forks[phi.left] = 1;
	display_message(philo, phi.left, RESET_COLOR,
		"has taken a left fork🥄");
	philo->data->forks[phi.right] = 1;
	display_message(philo, phi.left, RESET_COLOR,
		"has taken a right fork🥄");
	pthread_mutex_unlock(&philo->data->fork_locker[phi.left]);
	pthread_mutex_unlock(&philo->data->fork_locker[phi.right]);
	return (1);
}

int	eating(t_philo *philo, t_philo *phil)
{
	pthread_mutex_lock(&philo->data->endgame);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->endgame);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->endgame);
	display_message(philo, phil->id, GREEN, "is eating😋");
	pthread_mutex_lock(&philo->data->last_eat_locker);
	phil->last_eat_time = get_time();
	phil->count_eating_times++;
	pthread_mutex_unlock(&philo->data->last_eat_locker);
	waiting_time(philo->data->time_to_eat);
	return (1);
}

int	put_down_fork(t_philo *philo, t_philo phi)
{
	pthread_mutex_lock(&philo->data->endgame);
	printf("inside game %d\n", phi.id + 1);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->endgame);
		return (0);
	}
	printf("endgame its %d\n", phi.id + 1);
	pthread_mutex_unlock(&philo->data->endgame);
	pthread_mutex_lock(&philo->data->fork_locker[phi.right]);
	philo->data->forks[phi.right] = 0;
	pthread_mutex_unlock(&philo->data->fork_locker[phi.right]);
	pthread_mutex_lock(&philo->data->fork_locker[phi.left]);
	philo->data->forks[phi.left] = 0;
	pthread_mutex_unlock(&philo->data->fork_locker[phi.left]);
	display_message(philo, phi.left, RESET_COLOR,
		"has released a right fork🥄");
	display_message(philo, phi.left, RESET_COLOR,
		"has released a left fork🥄");
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
	display_message(philo, phi.left, YELLOW, "is sleeping😴");
	waiting_time(philo->data->time_to_sleep);
	return (1);
}
