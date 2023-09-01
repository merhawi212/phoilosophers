#include "philo.h"

void	display_log_message(t_philo *philo, int id, char *color, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	// pthread_mutex_lock(&philo->data->endgame);
	printf("%s%lld ms Philo %d %s\n"RESET_COLOR, color,
		get_time() - philo->data->start_time, id + 1, str);
	// pthread_mutex_unlock(&philo->data->endgame);
	pthread_mutex_unlock(&philo->data->print);
}

void	display_error_message(int i, int arg)
{
	if (i == -1)
		printf(RED"Arg number %d is null"RESET_COLOR, arg);
	else if (i == 0)
		printf(RED"Arg number %d should be greater than 0 \
				and should not beyond int max"RESET_COLOR, arg);
	else if (i == 1)
		printf(RED"Arg number %d is not numberic"RESET_COLOR, arg);
}
