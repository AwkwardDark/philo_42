/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:26:35 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/25 19:54:34 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*It uses a mutex to recover the death status in the shared data struct*/
int	ft_is_dead(t_data *data)
{
	if (data->dead->__align)
		return (1);
	return (0);
}

/*Gets all meals eaten flag*/
int	ft_is_finished(t_data *data)
{
	if (data->meal_nb != -1 && data->monitor->__align >= data->ph_nb * data->meal_nb)
		return (1);
	return (0);
}

/*Set death flag to stop the simulation*/
void	ft_set_death(t_data *data, t_philo *ph)
{
	ft_display(data, ph, 'D');
	sem_wait(data->dead);
	data->is_dead = 1;
	sem_post(data->dead);
}

/*Gets the value pf meal eaten with a mutex*/
int	ft_meal_counter(t_data *data, t_philo ph)
{
	int	val;

	sem_wait(data->monitor);
	val = ph.meals_eaten;
	sem_post(data->monitor);
	return (val);
}

/*Changes the flag to end the simulation*/
void	ft_set_end(t_data *data, t_philo *ph)
{	
	ft_display(data, ph, 'X');
	sem_wait(data->monitor);
	data->is_finished = 1;
	sem_post(data->monitor);
}
