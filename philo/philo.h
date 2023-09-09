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
# include <string.h>

# define TRUE 1
# define FALSE 0
# define RED "\033[31m"
# define BLUE "\033[34m"
# define YELLOW "\033[33m"
# define GREEN  "\033[32m"
# define CYAN "\033[35m"
# define RESET_COLOR "\033[0m"

typedef struct s_philo
{
	int				id;
	int				count_eating_times;
	int				left;
	int				right;
	long long		last_eat_time;
	pthread_t		p_thread;
	struct s_data	*data;
}		t_philo;

typedef struct s_data
{
	long long		start_time;
	int				dead;
	int				philo_num;
	int				times_must_eat;
	long long		time_to_eat;
	long long		time_to_die;
	long long		time_to_sleep;
	pthread_mutex_t	*fork_locker;
	pthread_mutex_t	print;
	pthread_mutex_t	endgame;
	pthread_mutex_t	last_eat_locker;
	pthread_mutex_t	eating_times_locker;
	int				*forks;
	t_philo			*philo;
}		t_data;

// utils.c
int			validate_args(char **argv);
long		ft_atoi(char *str);

// philo.c
int			create_fork(t_data *data);
int			create_philos(t_data *data);
int			create_thread(t_data *data);

//routine
void		*routine(void *philo);

// pickup_down_forks.c
int			pick_up_even_fork(t_philo *philo, t_philo phi);
int			pick_up_multiple_forks(t_philo *philo, t_philo phi);
int			put_down_fork(t_philo *philo, t_philo phi);

//time_handler.c
long long	get_time(void);
void		waiting_time(long long time);

// checker.c
int			is_dead(t_data *data);
int			checker(t_data *data);
int			is_someone_died(t_philo *philo);

// clear_free.c
int			thread_join(t_data *data);
void		destroy_mutexes(t_data *data);
void		destroy_free_fork(t_data *data);
void		clear_all(t_data *data);

// display_msg.c
void		display_log_message(t_philo *philo, int id, char *color, char *str);
void		display_error_message(int i, int arg);

#endif
