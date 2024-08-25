/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:00:00 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/25 21:36:27 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*It creates one thread per philosopher, and monitors each routine, making
sure that shared data is well used, once one philo dies or they ate all the
meals, the simulation ends properly*/
int	ft_simulation(t_data *data)
{
	t_philo	*ph;
	int		i;

	i = -1;
	ph = data->ph;
	data->t_start = ft_get_time();
	while (++i < data->ph_nb)
	{
		data->ph[i].t_last_meal = ft_get_time();
		if (pthread_create(&(ph[i].thread), NULL, &ft_routine, &ph[i]) != 0)
			return (printf(THREAD_ERR_1), 1);
	}
	if (data->ph_nb > 1)
		ft_monitor(data, ph);
	i = -1;
	while (++i < data->ph_nb)
	{
		if (pthread_join(ph[i].thread, NULL) != 0)
			return (printf(THREAD_ERR_2), 1);
	}
	if (ft_clear_mutex(data))
		return (1);
	return (0);
}

/*It takes one philo edge case, even philos must wait to eat, then the cycle
eat -> sleep -> think starts*/
void	*ft_routine(void *arg)
{
	t_philo	*ph;
	t_data	*data;

	ph = (t_philo *)arg;
	data = ph->data;
	if (data->ph_nb == 1)
		return (ft_one_philo(data, ph), NULL);
	if (ph->id % 2 == 0)
		ft_usleep(15);
	while (!ft_is_dead(data))
	{
		ft_eat(data, ph);
		if (ft_is_finished(data))
			break ;
		ft_display(data, ph, 'S');
		ft_usleep(data->t_sleep);
		ft_display(data, ph, 'T');
		usleep(100);
	}
	return (NULL);
}

/*Makes sure that philo stops after one dies, and checks the total number of
meals eaten*/
void	ft_monitor(t_data *data, t_philo *ph)
{
	int	i;

	while (!ft_is_finished(data))
	{
		i = -1;
		while (++i < data->ph_nb && !ft_is_dead(data))
		{
			pthread_mutex_lock(&data->meal);
			if (ft_get_time() - ph[i].t_last_meal >= data->t_die)
				ft_set_death(data, ph);
			pthread_mutex_unlock(&data->meal);
			usleep(10);
		}
		if (data->is_dead)
			break ;
		i = 0;
		while (i < data->ph_nb && data->meal_nb != -1
			&& ft_meal_counter(data, ph[i]) >= data->meal_nb)
			i++;
		if (i == data->ph_nb)
			ft_set_end(data, ph);
	}
}

/*It displays its own death*/
void	ft_one_philo(t_data *data, t_philo *ph)
{
	pthread_mutex_lock(&data->forks[ph->r_fork]);
	ft_display(data, ph, 'F');
	pthread_mutex_unlock(&data->forks[ph->r_fork]);
	ft_usleep(data->t_die);
	ft_display(data, ph, 'D');
}

/*Properly destroys all the mutex and free the fork and philo arrays*/
int	ft_clear_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->ph_nb)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			return (printf(THREAD_ERR_2), 1);
	}
	if (pthread_mutex_destroy(&data->write) != 0)
		return (printf(THREAD_ERR_2), 1);
	if (pthread_mutex_destroy(&data->meal) != 0)
		return (printf(THREAD_ERR_2), 1);
	if (pthread_mutex_destroy(&data->dead) != 0)
		return (printf(THREAD_ERR_2), 1);
	if (pthread_mutex_destroy(&data->monitor) != 0)
		return (printf(THREAD_ERR_2), 1);
	free(data->ph);
	free(data->forks);
	return (0);
}
