/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:49:07 by ekrause           #+#    #+#             */
/*   Updated: 2024/11/26 13:57:54 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_finished(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->nb_philo)
	{
		if (arg->philos[i].nb_meals < arg->must_eat)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor(void *data)
{
	t_arg	*arg;
	int		i;
	long	time_since_last_meal;

	arg = (t_arg *)data;
	while (!get_value(&arg->flag, arg))
	{
		i = -1;
		while (++i < arg->nb_philo)
		{
			time_since_last_meal = get_time() - arg->philos[i].last_meal;
			if ((time_since_last_meal > arg->time_to_die)
				|| (is_finished(arg) && arg->must_eat != -1))
			{
				if (time_since_last_meal > arg->time_to_die)
					write_status(&arg->philos[i], "died");
				pthread_mutex_lock(&arg->flag_mutex);
				arg->flag = 1;
				pthread_mutex_unlock(&arg->flag_mutex);
			}
		}
	}
	return (NULL);
}
