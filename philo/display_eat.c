/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:39:40 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/27 10:11:26 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Uses the mutex lock to display every routine action*/
void	ft_display(t_data *data, t_philo *ph, char c)
{
	long	time;

	pthread_mutex_lock(&data->write);
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
	pthread_mutex_unlock(&data->write);
}

/*Even and odd philos dont take the forks at the same order, a mutex is used
to register the last meal time and meal counter*/
void	ft_eat(t_data *data, t_philo *ph)
{
	if (ph->id % 2)
	{
		pthread_mutex_lock(&data->forks[ph->l_fork]);
		ft_display(data, ph, 'F');
		pthread_mutex_lock(&data->forks[ph->r_fork]);
		ft_display(data, ph, 'F');
	}
	else
	{
		pthread_mutex_lock(&data->forks[ph->r_fork]);
		ft_display(data, ph, 'F');
		pthread_mutex_lock(&data->forks[ph->l_fork]);
		ft_display(data, ph, 'F');
	}
	pthread_mutex_lock(&data->meal);
	ph->t_last_meal = ft_get_time();
	ph->meals_eaten++;
	pthread_mutex_unlock(&data->meal);
	ft_display(data, ph, 'E');
	ft_usleep(data->t_eat, data);
	pthread_mutex_unlock(&data->forks[ph->l_fork]);
	pthread_mutex_unlock(&data->forks[ph->r_fork]);
}
