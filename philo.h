/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:42:15 by marvin            #+#    #+#             */
/*   Updated: 2023/05/13 10:54:38 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# define TRUE 1
# define FALSE 0

typedef struct s_fork
{
	int	left;
	int	right;
}		t_fork;

typedef struct s_philo
{
	int				id;
	long long		last_eat_time;
	t_fork			*fork;
	enum {THINKING, EATING, SLEEPING}	*e_state;
}		t_philo;

typedef struct s_info
{
	pthread_t		*p_th;
	int				dead;
	int				n_thread;
	int				philo_num;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	pthread_mutex_t	*fork_locker;
	int				*forks;
	t_philo			*philo;
}		t_info;

// utils.c
void	display_message(int i, int arg);
void	validate_args(char **argv);
int		ft_atoi(char *str);

//routine
void	*routine(void *philo);


//thread_handler
int		create_thread(t_info *info);

//fork_handler
int		create_fork(t_info *info);

//time_handler
long long	get_time(void);
int		is_dead(t_info *info);
void	wating_time(int	time);
#endif
