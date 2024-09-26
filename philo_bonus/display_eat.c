/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:39:40 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/25 19:59:26 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*Uses the mutex lock to display every routine action*/
void	ft_display(t_data *data, t_philo *ph, char c)
{
	long	time;

	sem_wait(data->write);
	time = ft_get_time() - data->t_start;
	if (!ft_is_finished(data))
	{
		if (!ft_is_dead(data))
		{
			if (c == 'F')
				printf("%ld %d has taken a fork\n", time, ph->id);
			if (c == 'E')
				printf(BLUE "%ld %d is eating 🍝\n" RESET, time, ph->id);
			if (c == 'S')
				printf("%ld %d is sleeping\n", time, ph->id);
			if (c == 'T')
				printf("%ld %d is thinking\n", time, ph->id);
			if (c == 'D')
				printf(RED "%ld %d died 💀\n" RESET, time, ph->id);
			if (c == 'X')
				printf(G "%ld everyone finished their meal ! 🎉\n" RESET, time);
		}
	}
	sem_post(data->write);
}

/*Even and odd philos dont take the forks at the same order, a mutex is used
to register the last meal time and meal counter*/
void	ft_eat(t_data *data, t_philo *ph)
{
	sem_wait(data->forks);
	ft_display(data, ph, 'F');
	sem_wait(data->forks);
	ft_display(data, ph, 'F');
	sem_wait(data->meal);
	ph->t_last_meal = ft_get_time();
	ph->meals_eaten++;
	sem_post(data->meal);
	ft_display(data, ph, 'E');
	ft_usleep(data->t_eat, data);
	sem_post(data->monitor);
	sem_post(data->forks);
	sem_post(data->forks);
}
