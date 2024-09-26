/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:37:16 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/26 17:40:23 by pajimene         ###   ########.fr       */
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
	if (data->meal_nb != -1 && data->meal_monitor->__align >= data->ph_nb * data->meal_nb)
		return (1);
	return (0);
}
