/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:14:25 by ekrause           #+#    #+#             */
/*   Updated: 2024/11/28 13:57:54 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	destroy_all(t_arg *arg)
{
	int	i;

	i = -1;
	while (++i < arg->nb_philo)
		pthread_mutex_destroy(&arg->forks[i].fork);
	pthread_mutex_destroy(&arg->value_mutex);
	free(arg->philos);
	free(arg->forks);
	free(arg);
}

static int	check_if_one_philo(t_arg *arg)
{
	if (arg->nb_philo == 1)
	{
		write_status(&arg->philos[0], "is thinking");
		usleep(arg->time_to_die * 1000);
		write_status(&arg->philos[0], "died");
		return (1);
	}
	return (0);
}

int	launch_thread(t_arg *arg)
{
	int	i;

	i = 0;
	if (pthread_create(&arg->monitor_thread, NULL, monitor, (void *)arg) != 0)
		return (-1);
	while (i < arg->nb_philo)
	{
		if (pthread_create(&arg->philos[i].philo, NULL, routine,
				(void *)&arg->philos[i]) != 0)
			return (-1);
		i++;
	}
	return (1);
}

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
	if (check_if_one_philo(arg))
		return (free(arg->philos), free(arg->forks), free(arg), 0);
	if (!launch_thread(arg))
		return (free(arg->philos), free(arg->forks), free(arg),
			ft_error("failed to create thread"), 1);
	i = 0;
	while (i < arg->nb_philo)
		pthread_join(arg->philos[i++].philo, NULL);
	pthread_join(arg->monitor_thread, NULL);
	destroy_all(arg);
	return (0);
}
