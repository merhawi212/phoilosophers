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
		return (destroy_free_fork(data), FALSE);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	int			philo_num;
	t_data		*data;

	if (argc == 5 || argc == 6)
	{
		if (!validate_args(argv + 1))
			return (0);
		philo_num = ft_atoi(argv[1]);
		data = malloc(sizeof(t_data));
		if (!init_data(data, argv, argc, philo_num))
		{
			destroy_mutexes(data);
			return (free(data), 0);
		}
		if (create_thread(data) == FALSE)
		{
			thread_join(data);
			return (clear_all(data), 0);
		}
	}
	return (0);
}
