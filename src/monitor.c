/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:49:07 by ekrause           #+#    #+#             */
/*   Updated: 2024/11/20 20:08:12 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int is_finished(t_arg *arg)
{
	int i;

	i = 0;
	while (i < arg->nb_philo)
	{
		if (arg->philos[i].nb_meals < arg->must_eat)
			return (0);
		i++;
	}
	return (1);
}

void *monitor(void *data)
{
	t_arg *arg = (t_arg *)data;
	int i;
	long time_since_last_meal;

	while (!arg->flag)
	{
		i = 0;
		while (i < arg->nb_philo)
		{
			time_since_last_meal = get_time() - arg->philos[i].last_meal;
			if (time_since_last_meal > arg->time_to_die)
			{
				write_status(&arg->philos[i], "died");
				pthread_mutex_lock(&arg->flag_mutex);
				arg->flag = 1;
				pthread_mutex_unlock(&arg->flag_mutex);
				break ;
			}
			if (is_finished(arg) && arg->must_eat != -1)
			{
				write_status(&arg->philos[i], "finished eating");
				pthread_mutex_lock(&arg->flag_mutex);
				arg->flag = 1;
				pthread_mutex_unlock(&arg->flag_mutex);
				break ;
			}
			i++;
		}
	}
	return (NULL);
}
