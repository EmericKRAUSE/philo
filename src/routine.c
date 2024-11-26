/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:46:05 by ekrause           #+#    #+#             */
/*   Updated: 2024/11/26 13:48:14 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_if_one_philo(t_philo *philo)
{
	if (philo->arg->nb_philo == 1)
	{
		write_status(philo, "is thinking");
		usleep(philo->arg->time_to_die * 1000);
		write_status(philo, "died");
		return (1);
	}
	return (0);
}

bool	get_value(bool *value, t_arg *data)
{
	bool	v;

	pthread_mutex_lock(&data->write_mutex);
	v = *value;
	pthread_mutex_unlock(&data->write_mutex);
	return (v);
}

void	*routine(void *data)
{
	t_philo			*philo;
	t_arg			*arg;

	philo = (t_philo *)data;
	arg = (t_arg *)philo->arg;
	if (check_if_one_philo(philo))
		return (NULL);
	if (philo->id % 2)
		usleep(15000);
	while (!get_value(&arg->flag, arg))
	{
		pthread_mutex_lock(&philo->l_fork->fork);
		write_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->r_fork->fork);
		write_status(philo, "has taken a fork");
		philo->last_meal = get_time();
		philo->nb_meals++;
		write_status(philo, "is eating");
		usleep(arg->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->r_fork->fork);
		pthread_mutex_unlock(&philo->l_fork->fork);
		write_status(philo, "is sleeping");
		usleep(arg->time_to_sleep * 1000);
	}
	return (NULL);
}
