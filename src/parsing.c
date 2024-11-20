/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:50:37 by ekrause           #+#    #+#             */
/*   Updated: 2024/11/20 17:51:39 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_numeric(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = 0;
		if (argv[i][j] == '\0' || argv[i][j] == '0' || ft_strlen(argv[i]) > 9)
			return (0);
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
	}
	return (1);
}

int	parse_arg(int argc, char **argv)
{
	if ((argc == 5 || argc == 6) && is_numeric(argv))
		return (1);
	return (0);
}
