/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:30:49 by ekrause           #+#    #+#             */
/*   Updated: 2024/11/20 20:05:49 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	write_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->arg->write_mutex);
	if (!philo->arg->flag)
		printf(D_GREEN "[%ld] %ld %s\n" D_RESET,
			   get_time() - philo->arg->start,
			   philo->id,
			   status);
	pthread_mutex_unlock(&philo->arg->write_mutex);
}

long get_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int ft_atoi(const char *str)
{
	int sign;
	int result;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - 48;
		str++;
	}
	return (result * sign);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_error(char *error)
{
	printf(D_RED "%s\n" D_RESET, error);
}