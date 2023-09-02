/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:09:33 by marvin            #+#    #+#             */
/*   Updated: 2023/09/02 14:35:24 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*the last while loop of this atoi is an extra validation 
	than the norm and that is if there is any non numberic char in between 
	or after the numbers (+ or -), it will throw an error (returns 0).
 */

static void	remove_leading_zeros_whitespaces(char *str, int *i)
{
	while (str[*i] && ((str[*i] >= 9 && str[*i] <= 13)
			|| str[*i] == ' ' || str[*i] == '0'))
		(*i)++;
}

long	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	result;
	int		count;

	i = 0;
	sign = 1;
	result = 0;
	remove_leading_zeros_whitespaces(str, &i);
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] && str[i] == '0')
		i++;
	count = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + (str[i++] - '0');
		if (++count > 10 || result > 2147483647)
			return (0);
	}
	while (str[i] && !(str[i] >= '0' && str[i] <= '9'))
		return (0);
	return (result * sign);
}

static int	is_num(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9') 
				|| str[i] == '+' || str[i] == '-'))
			return (0);
		i++;
	}
	return (1);
}

int	validate_args(char **argv)
{
	int	i;

	i = 0;
	if (!argv[i])
		return (display_error_message(-1, 1), 0);
	while (argv[i])
	{
		if (!argv[i] || !argv[i][0])
			return (display_error_message(-1, i + 1), 0);
		if (!is_num(argv[i]))
			return (display_error_message(1, i + 1), 0);
		if (argv[i][0] == '0' && argv[i][1] == '\0')
			return (display_error_message(0, i + 1), 0);
		if (ft_atoi(argv[i]) <= 0)
			return (display_error_message(0, i + 1), 0);
		i++;
	}
	return (1);
}
