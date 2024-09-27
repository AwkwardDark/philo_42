/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:46:58 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/27 16:03:28 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Checking that argument values fit the subject requirements*/
static int	ft_check_input(t_data *data)
{
	if (data->ph_nb == 0 || data->ph_nb > 200)
		return (1);
	if (data->meal_nb == 0 || data->meal_nb > INT_MAX)
		return (1);
	if (data->t_die == 0 || data->t_die > INT_MAX)
		return (1);
	if (data->t_eat == 0 || data->t_eat > INT_MAX)
		return (1);
	if (data->t_sleep == 0 || data->t_sleep > INT_MAX)
		return (1);
	return (0);
}

/*Parsing argv input into data structure*/
int	ft_data_init(t_data *data, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_check_syntax(av[i]))
			return (printf(SYNTAX_ERR), 1);
		i++;
	}
	data->ph_nb = ft_atol(av[1]);
	data->t_die = ft_atol(av[2]);
	data->t_eat = ft_atol(av[3]);
	data->t_sleep = ft_atol(av[4]);
	data->meal_nb = -1;
	data->is_dead = 0;
	data->is_finished = 0;
	if (av[5])
		data->meal_nb = ft_atol(av[5]);
	if (ft_check_input(data))
		return (printf(DATA_ERR), 1);
	return (0);
}

/*Initializing all of data structure mutexes*/
int	ft_init_mutex_data(t_data *data)
{
	int	i;

	i = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->ph_nb);
	if (!data->forks)
		return (printf(MALL_ERR), 1);
	while (++i < data->ph_nb)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (printf(MUTEX_ERR_1), 1);
	}
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (printf(MUTEX_ERR_1), 1);
	if (pthread_mutex_init(&data->meal, NULL) != 0)
		return (printf(MUTEX_ERR_1), 1);
	if (pthread_mutex_init(&data->dead, NULL) != 0)
		return (printf(MUTEX_ERR_1), 1);
	if (pthread_mutex_init(&data->monitor, NULL) != 0)
		return (printf(MUTEX_ERR_1), 1);
	return (0);
}

/*Initiliazing each philo dataset*/
int	ft_philo_init(t_data *data)
{
	int	i;

	data->ph = malloc(sizeof(t_philo) * data->ph_nb);
	if (!data->ph)
		return (printf(MALL_ERR), 1);
	i = -1;
	while (++i < data->ph_nb)
	{
		data->ph[i].data = data;
		data->ph[i].id = i + 1;
		data->ph[i].meals_eaten = 0;
		data->ph[i].r_fork = i;
		data->ph[i].l_fork = (i + 1) % data->ph_nb;
	}
	return (0);
}
