/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:14:25 by ekrause           #+#    #+#             */
/*   Updated: 2024/11/20 19:48:41 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_arg	*arg;
	int		i;

	if (!parse_arg(argc, argv))
		return (ft_error("error"), 1);
	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (ft_error("allocation failed"), 1);
	init_arg(argc, argv, &arg);
	init_philos_and_forks(&arg);
	if (pthread_create(&arg->monitor_thread, NULL, monitor, (void *)arg) != 0)
		return (free(arg), ft_error("failed to create thread"), 1);
	i = -1;
	while (++i < arg->nb_philo)
	{
		if (pthread_create(&arg->philos[i].philo, NULL, routine, (void *)&arg->philos[i]) != 0)
			return (free(arg), ft_error("failed to create thread"), 1);
	}
	i = -1;
	while (++i < arg->nb_philo)
		pthread_join(arg->philos[i].philo, NULL);
	pthread_join(arg->monitor_thread, NULL);
	i = -1;
	while (++i < arg->nb_philo)
		pthread_mutex_destroy(&arg->forks[i].fork);
	pthread_mutex_destroy(&arg->flag_mutex);
	pthread_mutex_destroy(&arg->rdy_mutex);
	pthread_mutex_destroy(&arg->write_mutex);
	free(arg->philos);
	free(arg->forks);
	return (free(arg), 0);
}