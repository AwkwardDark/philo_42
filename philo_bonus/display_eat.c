/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:37:22 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/26 18:34:00 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*Uses the mutex lock to display every routine action*/
void	ft_display(t_data *data, t_philo *ph, char c)
{
	long	time;

	time = ft_get_time() - data->t_start;
	sem_wait(data->write);
	if (!ft_is_finished(data))
	{
		if (!ft_is_dead(data))
		{
			if (c == 'F' && !ft_is_dead(data))
				printf(RESET "%ld %d has taken a fork\n", time, ph->id);
			if (c == 'E' && !ft_is_dead(data))
				printf(BLUE "%ld %d is eating 🍝\n" RESET, time, ph->id);
			if (c == 'S' && !ft_is_dead(data))
				printf(RESET "%ld %d is sleeping\n", time, ph->id);
			if (c == 'T' && !ft_is_dead(data))
				printf(RESET "%ld %d is thinking\n", time, ph->id);
			if (c == 'D' && !ft_is_dead(data))
				printf(RED "%ld %d died 💀\n" RESET, time, ph->id);
		}
	}
	sem_post(data->write);
}

/*Even and odd philos dont take the forks at the same order, a mutex is used
to register the last meal time and meal counter*/
void	ft_eat_sleep_think(t_data *data, t_philo *ph)
{
	sem_wait(data->forks);
	ft_display(data, ph, 'F');
	sem_wait(data->forks);
	ft_display(data, ph, 'F');
	sem_wait(data->meal);
	ph->t_last_meal = ft_get_time();
	sem_post(data->meal);
	ft_display(data, ph, 'E');
	sem_post(data->meal_monitor);
	if (ft_is_finished(data))
		return ;
	ft_usleep(data->t_eat, data);
	sem_post(data->forks);
	sem_post(data->forks);
	ft_display(data, ph, 'S');
	ft_usleep(data->t_sleep, data);
	ft_display(data, ph, 'T');
	usleep(100);
}
