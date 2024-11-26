/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:53:47 by ekrause           #+#    #+#             */
/*   Updated: 2024/11/26 15:50:23 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_arg(int argc, char **argv, t_arg **arg)
{
	(*arg)->nb_philo = ft_atoi(argv[1]);
	(*arg)->time_to_die = ft_atoi(argv[2]);
	(*arg)->time_to_eat = ft_atoi(argv[3]);
	(*arg)->time_to_sleep = ft_atoi(argv[4]);
	(*arg)->start = get_time();
	(*arg)->flag = false;
	(*arg)->last_philo_rdy = false;
	pthread_mutex_init(&(*arg)->value_mutex, NULL);
	if (argc == 6)
		(*arg)->must_eat = ft_atoi(argv[5]);
	else
		(*arg)->must_eat = -1;
}

void	init_philos_and_forks(t_arg **arg)
{
	int	i;

	(*arg)->philos = malloc(sizeof(t_philo) * (*arg)->nb_philo);
	(*arg)->forks = malloc(sizeof(t_fork) * (*arg)->nb_philo);
	if (!(*arg)->philos || !(*arg)->forks)
		return ;
	i = -1;
	while (++i < (*arg)->nb_philo)
	{
		(*arg)->philos[i].id = i;
		(*arg)->forks[i].id = i;
		(*arg)->philos[i].last_meal = (*arg)->start;
		(*arg)->philos[i].nb_meals = 0;
		(*arg)->philos[i].l_fork = &(*arg)->forks[i];
		(*arg)->philos[i].r_fork = &(*arg)->forks[(i + 1) % (*arg)->nb_philo];
		(*arg)->philos[i].arg = *arg;
		pthread_mutex_init(&(*arg)->forks[i].fork, NULL);
	}
}
