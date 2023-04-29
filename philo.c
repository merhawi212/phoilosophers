/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:45:29 by marvin            #+#    #+#             */
/*   Updated: 2023/04/29 19:28:39 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t mutex;

void	test(t_philo *philo, int left, int right, int i)
{
	if (philo->e_state[left] != EATING
		&& philo->e_state[right] != EATING
		&& philo->e_state[i] != EATING)
	{
		pthread_mutex_lock(&mutex);
		philo->e_state[i] = EATING;
		sleep(2);
		printf("Philo %d is taking fork %d (left) and %d (right)\n",
			i + 1, left + 1, right + 1);
		printf("Philo %d is eating\n", i + 1);
		pthread_mutex_unlock(&mutex);
	}
}

void	pick_up_fork(t_philo *philo, int i)
{
	// int	i;
	int	left;
	int	right;

	// i = *(int *)philo->philos;
	// pthread_mutex_lock(&mutex);
	philo->e_state[i] = SLEEPING;
	printf("here its");
	left = philo->philo_info[i].fork.left;
	right = philo->philo_info[i].fork.right;
	pthread_mutex_lock(&philo->forks[left]);
	pthread_mutex_lock(&philo->forks[right]);
	philo->e_state[i] = THINKING;
	// printf("\n philoshoper %d\n", i + 1);
	printf("Philo %d is thinking\n", i + 1);
	sleep(1);
	test(philo, left, right, i);
	// pthread_mutex_unlock(&mutex);
}

void	put_down_fork(t_philo *philo, int i)
{
	// int	i;
	int	left;
	int	right;

	// i = *(int *)philo->philos;
	philo->e_state[i] = SLEEPING;
	left = philo->philo_info[i].fork.left;
	right = philo->philo_info[i].fork.right;
	printf("Philo %d is puting fork %d and %d \n",
		i + 1, left + 1, right + 1);
	printf("Philo %d is sleeping\n", i + 1);
	// sleep(1);
	pthread_mutex_unlock(&philo->forks[left]);
	pthread_mutex_unlock(&philo->forks[right]);
	// pthread_mutex_unlock(&mutex);
}

void	philoshoper(void *philo)
{
	t_philo		*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		printf("||philo here its ||");
		pick_up_fork(ph, *ph->philos);
		put_down_fork(ph, *ph->philos);
		usleep(100);
	}
}

void	create_thread(t_philo *philo, char **argv, int num)
{
	int	i;

	philo->phnum = num;
	i = -1;
	pthread_mutex_init(&mutex, NULL);
	while (++i < num)
		pthread_mutex_init(&philo->forks[i], NULL);
	i = -1;
	while (++i < num)
	{
		philo->philo_info[i].id = i;
		philo->philo_info[i].fork.left = i % num;
		philo->philo_info[i].fork.right = (i + 1) % num;
		*philo->philos = i;
		pthread_create(&philo->p_th[i], NULL, &philoshoper, (void *) philo);
	}
	i = -1;
	while (++i < num)
		pthread_join(philo->p_th[i], NULL);
	i = -1;
	free(philo->p_th);
	free(philo->e_state);
	free(philo->philos);
	while (++i < num)
		pthread_mutex_destroy(&philo->forks[i]);
	pthread_mutex_destroy(&mutex);
	free(philo->forks);
}

int	main(int argc, char **argv)
{
	int			num;
	t_philo		philo;

	if (argc == 5)
	{
		// validate_args(argv + 1);
		num = ft_atoi(argv[1]);
		if (num <= 0)
			display_message(2, 1);
		philo.p_th = malloc(sizeof(pthread_t) * num + 1);
		if (!philo.p_th)
			return (0);
		philo.forks = malloc(sizeof(pthread_mutex_t) * num + 1);
		if (!philo.forks)
			return (0);
		philo.e_state = malloc(sizeof(int) * num + 1);
		if (!philo.e_state)
			return (0);
		philo.philo_info = malloc(sizeof(t_philo_info) * num + 1);
		create_thread(&philo, argv + 1, num);
	}
}

// philo.philos = malloc(sizeof(int) * len);
// if (!philo.philos)
// 	return (0);
// philo.forks = malloc(sizeof(int) * len);
// if (!philo.forks)
// 	return (0);
// i = -1;
// while (++i < len)
// {
// 	philo.philos[i] = i;
// 	philo.forks[i] = i;
// }