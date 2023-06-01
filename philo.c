/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:36:01 by mkiflema          #+#    #+#             */
/*   Updated: 2023/05/13 10:52:07 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_info *info)
{
	int	i;

	i = -1;
	free(info->p_th);
	while (++i < info->philo_num)
		pthread_mutex_destroy(&info->fork_locker[i]);
	free(info->forks);
	free(info->fork_locker);
	free(info->philo);
}

void	feed_philo(t_info *info, char **argv, int philo_num)
{
	int	i;
	long long	current_time;

	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->dead = 0;
	info->flag = 1;
	i = -1;
	current_time = get_time();
	while (++i < info->philo_num)
	{
		info->philo[i].id = i;
		info->philo[i].left = i;
		info->philo[i].right = (i + 1) % info->philo_num;
		info->philo[i].last_eat_time = current_time;

	}
}

int	create_philos(t_info *info, char **argv, int philo_num)
{
	int	i;

	info->philo_num = philo_num;
	info->philo = malloc(sizeof(t_philo) * (philo_num + 1));
	if (!info->philo)
		return (FALSE);
	feed_philo(info, argv, philo_num);
	return (TRUE);
}

// void	*routine_one(void *info)
// {
// 	t_info	*inf;

// 	inf = (t_info *)info;
// }

// void 	only_one_philo(t_info *info)
// {
// 	info->p_th = malloc(sizeof(pthread_t) * info->philo_num + 1);
// 	if (!info->p_th)
// 		return (FALSE);
// 	info->n_thread = 0;
// 	if (pthread_create(&info->p_th[0], NULL, &routine_one, (void *)info) != 0)
// 		return (FALSE);
// 	while (info->dead == 0)
// 		wating_time(1);
	
// }

int	main(int argc, char **argv)
{
	int			num;
	t_info		info;

	if (argc == 5)
	{
		validate_args(argv + 1);
		num = ft_atoi(argv[1]);
		if (num <= 0)
			display_message(2, 1);
		if (!create_philos(&info, argv, num))
			return (FALSE);
		if (!create_fork(&info))
			return (FALSE);
		if (create_thread(&info) == FALSE)
			return (FALSE);
		destroy_mutex(&info);
	}
}
