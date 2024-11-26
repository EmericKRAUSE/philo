/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:49:07 by ekrause           #+#    #+#             */
/*   Updated: 2024/11/26 14:57:51 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_finished(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < get_long(&arg->nb_philo, arg))
	{
		if (get_long(&arg->philos[i].nb_meals, arg) < get_long(&arg->must_eat, arg))
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
	while (!get_bool(&arg->flag, arg))
	{
		i = -1;
		while (++i < get_long(&arg->nb_philo, arg))
		{
			time_since_last_meal = get_time() - get_long(&arg->philos[i].last_meal, arg);
			if ((time_since_last_meal > get_long(&arg->time_to_die, arg))
				|| (is_finished(arg) && get_long(&arg->must_eat, arg) != -1))
			{
				if (time_since_last_meal > get_long(&arg->time_to_die, arg))
					write_status(&arg->philos[i], "died");
				pthread_mutex_lock(&arg->value_mutex);
				arg->flag = 1;
				pthread_mutex_unlock(&arg->value_mutex);
			}
		}
	}
	return (NULL);
}
