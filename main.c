/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:01:19 by mkiflema          #+#    #+#             */
/*   Updated: 2023/08/31 19:38:13 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_join(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		pthread_join(data->philo[i].p_thread, NULL);
	return (TRUE);
}

void	clear_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_destroy(&data->fork_locker[i]);
	}
	pthread_mutex_destroy(&data->last_eat_locker);
	pthread_mutex_destroy(&data->endgame);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->eating_times_locker);
	free(data->forks);
	free(data->fork_locker);
	free(data->philo);
	free(data);
	return ;
}

static int	init_data(t_data *data, char **argv, int argc, int philo_num)
{
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->times_must_eat = 0;
	if (argc == 6)
		data->times_must_eat = ft_atoi(argv[5]);
	data->dead = 0;
	data->philo_num = philo_num;
	pthread_mutex_init(&data->last_eat_locker, NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->endgame, NULL);
	pthread_mutex_init(&data->eating_times_locker, NULL);
	if (!create_fork(data))
		return (FALSE);
	if (!create_philos(data))
		return (FALSE);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	int			philo_num;
	t_data		*data;

	if (argc == 5 || argc == 6)
	{
		validate_args(argv + 1, argc);
		philo_num = ft_atoi(argv[1]);
		data = malloc(sizeof(t_data));
		if (!init_data(data, argv, argc, philo_num))
		{
			clear_all(data);
			return (1);
		}
		if (create_thread(data) == FALSE)
		{
			thread_join(data);
			clear_all(data);
			return (1);
		}
	}
	return (0);
}
