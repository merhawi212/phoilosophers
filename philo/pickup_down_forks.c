/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickup_down_forks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 13:21:04 by mkiflema          #+#    #+#             */
/*   Updated: 2023/09/09 20:09:53 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	even_fork_msg_logger(t_philo *philo, t_philo phi)
{
	philo->data->forks[phi.left] = -1;
	display_log_message(philo, phi.left, RESET_COLOR,
		"has taken a left fork🥄");
	philo->data->forks[phi.right] = -1;
	display_log_message(philo, phi.left, RESET_COLOR,
		"has taken a right fork🥄");
	pthread_mutex_unlock(&philo->data->fork_locker[phi.right]);
	pthread_mutex_unlock(&philo->data->fork_locker[phi.left]);
}

int	pick_up_even_fork(t_philo *philo, t_philo phi)
{
	pthread_mutex_lock(&philo->data->fork_locker[phi.right]);
	pthread_mutex_lock(&philo->data->fork_locker[phi.left]);
	while (philo->data->forks[phi.left] == -1 
		|| philo->data->forks[phi.right] == -1
		|| philo->data->forks[phi.left] == phi.id
		|| philo->data->forks[phi.right] == phi.id)
	{
		pthread_mutex_unlock(&philo->data->fork_locker[phi.right]);
		pthread_mutex_unlock(&philo->data->fork_locker[phi.left]);
		pthread_mutex_lock(&philo->data->endgame);
		if (philo->data->dead)
			return (pthread_mutex_unlock(&philo->data->endgame), 0);
		pthread_mutex_unlock(&philo->data->endgame);
		usleep(1);
		pthread_mutex_lock(&philo->data->fork_locker[phi.right]);
		pthread_mutex_lock(&philo->data->fork_locker[phi.left]);
	}
	even_fork_msg_logger(philo, phi);
	return (1);
}

static void	odd_forks_msg_logger(t_philo *philo, t_philo phi)
{
	philo->data->forks[phi.left] = -1;
	display_log_message(philo, phi.left, RESET_COLOR,
		"has taken a left fork🥄");
	philo->data->forks[phi.right] = -1;
	display_log_message(philo, phi.left, RESET_COLOR,
		"has taken a right fork🥄");
	pthread_mutex_unlock(&philo->data->fork_locker[phi.left]);
	pthread_mutex_unlock(&philo->data->fork_locker[phi.right]);
}

int	pick_up_multiple_forks(t_philo *philo, t_philo phi)
{
	display_log_message(philo, phi.id, BLUE, "is thinking🤔");
	if ((phi.id + 1) % 2 == 0)
	{
		if (!pick_up_even_fork(philo, phi))
			return (0);
		return (1);
	}
	pthread_mutex_lock(&philo->data->fork_locker[phi.left]);
	pthread_mutex_lock(&philo->data->fork_locker[phi.right]);
	while (philo->data->forks[phi.left] == -1 
		|| philo->data->forks[phi.right] == -1
		|| philo->data->forks[phi.left] == phi.id
		|| philo->data->forks[phi.right] == phi.id)
	{
		pthread_mutex_unlock(&philo->data->fork_locker[phi.left]);
		pthread_mutex_unlock(&philo->data->fork_locker[phi.right]);
		pthread_mutex_lock(&philo->data->endgame);
		if (philo->data->dead)
			return (pthread_mutex_unlock(&philo->data->endgame), 0);
		pthread_mutex_unlock(&philo->data->endgame);
		usleep(1);
		pthread_mutex_lock(&philo->data->fork_locker[phi.left]);
		pthread_mutex_lock(&philo->data->fork_locker[phi.right]);
	}
	return (odd_forks_msg_logger(philo, phi), 1);
}

int	put_down_fork(t_philo *philo, t_philo phi)
{
	pthread_mutex_lock(&philo->data->endgame);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->endgame);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->endgame);
	pthread_mutex_lock(&philo->data->fork_locker[phi.right]);
	philo->data->forks[phi.right] = phi.id;
	display_log_message(philo, phi.left, RESET_COLOR,
		"has released a right fork🥄");
	pthread_mutex_unlock(&philo->data->fork_locker[phi.right]);
	pthread_mutex_lock(&philo->data->fork_locker[phi.left]);
	philo->data->forks[phi.left] = phi.id;
	display_log_message(philo, phi.left, RESET_COLOR,
		"has released a left fork🥄");
	pthread_mutex_unlock(&philo->data->fork_locker[phi.left]);
	return (1);
}
