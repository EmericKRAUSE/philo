/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:14:44 by ekrause           #+#    #+#             */
/*   Updated: 2024/11/26 15:52:11 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//**********/
// library
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/time.h>

//**********/
// defines
# define D_RED	"\033[31m"
# define D_GREEN "\033[32m"
# define D_RESET	"\033[0m"

//**********/
// structures
typedef struct s_arg	t_arg;
typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;

typedef struct s_arg
{
	long			nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat;
	long			start;
	bool			flag;
	bool			last_philo_rdy;
	pthread_mutex_t	value_mutex;
	t_philo			*philos;
	t_fork			*forks;
	pthread_t		monitor_thread;
}	t_arg;

typedef struct s_philo
{
	long		id;
	pthread_t	philo;
	long		last_meal;
	long		nb_meals;
	t_fork		*l_fork;
	t_fork		*r_fork;
	t_arg		*arg;
}	t_philo;

typedef struct s_fork
{
	long			id;
	pthread_mutex_t	fork;	
}	t_fork;

//**********/
// prototypes

// init.c
void	init_arg(int argc, char **argv, t_arg **arg);
void	init_philos_and_forks(t_arg **arg);
//

// monitor.c
void	*monitor(void *data);
//

// parsing.c
int		parse_arg(int argc, char **argv);
//

// routine.c
void	*routine(void *data);
//

// utils.c
bool	get_bool(bool *value, t_arg *data);
long	get_long(long *value, t_arg *data);
void	write_status(t_philo *philo, char *status);
long	get_time(void);
int		ft_atoi(const char *str);
void	ft_error(char *error);
int		ft_strlen(char *str);
//

//**********

#endif