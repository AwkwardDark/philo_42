/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:26:35 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/27 12:17:54 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*It uses a mutex to recover the death status in the shared data struct*/
int	ft_is_dead(t_data *data)
{
	int	val;

	pthread_mutex_lock(&data->dead);
	val = data->is_dead;
	pthread_mutex_unlock(&data->dead);
	return (val);
}

/*Gets all meals eaten flag*/
int	ft_is_finished(t_data *data)
{
	int	val;

	pthread_mutex_lock(&data->monitor);
	val = data->is_finished;
	pthread_mutex_unlock(&data->monitor);
	return (val);
}

/*Set death flag to stop the simulation*/
void	ft_set_death(t_data *data, t_philo *ph)
{
	ft_display(data, ph, 'D');
	pthread_mutex_lock(&data->dead);
	data->is_dead = 1;
	pthread_mutex_unlock(&data->dead);
}

/*Gets the value pf meal eaten with a mutex*/
int	ft_meal_counter(t_data *data, t_philo *ph)
{
	int	val;

	pthread_mutex_lock(&data->meal);
	val = ph->meals_eaten;
	pthread_mutex_unlock(&data->meal);
	return (val);
}

/*Changes the flag to end the simulation*/
void	ft_set_end(t_data *data, t_philo *ph)
{	
	ft_display(data, ph, 'X');
	pthread_mutex_lock(&data->monitor);
	data->is_finished = 1;
	pthread_mutex_unlock(&data->monitor);
}
