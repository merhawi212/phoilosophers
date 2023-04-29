/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:42:15 by marvin            #+#    #+#             */
/*   Updated: 2023/04/29 19:06:03 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_fork
{
	int	left;
	int	right;
}		t_fork;

typedef struct s_philo_info
{
	int		id;
	int		*last_eat_time;
	int		time_to_eat;
	int		time_to_die;
	t_fork	fork;
}		t_philo_info;

typedef struct s_philo
{
	pthread_t		*p_th;
	pthread_mutex_t	*forks;
	int				phnum;
	int				*philos;
	t_philo_info	*philo_info;
	enum {THINKING, EATING, SLEEPING}	*e_state;
}		t_philo;

// utils.c
void	display_message(int i, int arg);
void	validate_args(char **argv);
int		ft_atoi(char *str);

#endif
