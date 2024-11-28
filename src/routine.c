/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:46:05 by ekrause           #+#    #+#             */
/*   Updated: 2024/11/28 13:34:16 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	eating_process(t_arg *arg, t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork->fork);
	write_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->r_fork->fork);
	write_status(philo, "has taken a fork");
	pthread_mutex_lock(&arg->value_mutex);
	philo->last_meal = get_time();
	philo->nb_meals++;
	pthread_mutex_unlock(&arg->value_mutex);
	write_status(philo, "is eating");
	usleep(arg->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->l_fork->fork);
	pthread_mutex_unlock(&philo->r_fork->fork);
}

void	*routine(void *data)
{
	t_philo			*philo;
	t_arg			*arg;

	philo = (t_philo *)data;
	arg = (t_arg *)philo->arg;
	if (philo->id % 2)
		usleep(arg->time_to_eat);
	while (!get_bool(&arg->flag, arg))
	{
		eating_process(arg, philo);
		write_status(philo, "is sleeping");
		usleep(arg->time_to_sleep * 1000);
	}
	return (NULL);
}
