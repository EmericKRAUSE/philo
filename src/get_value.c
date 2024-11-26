/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:55:24 by ekrause           #+#    #+#             */
/*   Updated: 2024/11/26 14:56:00 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long get_long(long *value, t_arg *data)
{
	long v;

	pthread_mutex_lock(&data->value_mutex);
	v = *value;
	pthread_mutex_unlock(&data->value_mutex);
	return (v);
}

bool get_bool(bool *value, t_arg *data)
{
	bool v;

	pthread_mutex_lock(&data->value_mutex);
	v = *value;
	pthread_mutex_unlock(&data->value_mutex);
	return (v);
}
