/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:46:58 by pajimene          #+#    #+#             */
/*   Updated: 2024/06/27 17:17:32 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atol(char *str)
{
	long	nbr;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	nbr = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - 48);
		i++;
	}
	return (nbr * sign);
}

int	ft_check_syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_data(t_data *data)
{
	if (data->number == 0)
		return (1);
	if (data->time_die < 60)
		return (1);
	if (data->time_eat < 60)
		return (1);
	if (data->time_sleep < 60)
		return (1);
	return (0);
}

int	ft_parse_input(t_data *data, char **av)
{
	int	i;
	(void)data;

	i = 1;
	while (av[i])
	{
		if (ft_check_syntax(av[i]))
			return(printf(SYNTAX_ERR), 1);
		i++;
	}
	data->number = ft_atol(av[1]);
	data->time_die = ft_atol(av[2]);
	data->time_eat = ft_atol(av[3]);
	data->time_sleep = ft_atol(av[4]);
	if (ft_check_data(data))
		return (printf(DATA_ERR), 1);
	return(0);
}
