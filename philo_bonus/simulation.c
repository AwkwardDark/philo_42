/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:00:00 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/25 20:18:08 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*It creates one thread per philosopher, and monitors each routine, making
sure that shared data is well used, once one philo dies or they ate all the
meals, the simulation ends properly*/
int ft_simulation(t_data *data)
{
	int i;
	int status; //why?

	i = -1;
	data->t_start = ft_get_time();
	while (++i < data->ph_nb)
	{
		data->ph[i].pid = fork();
		data->ph[i].t_last_meal = ft_get_time();
		if (data->ph[i].pid == -1)
			return (printf(FORK_ERR), 1);
		if (data->ph[i].pid == 0)
			ft_routine(data, &data->ph[i]);
	}
	waitpid(-1, &status, 0);
	if (status != 0)
	{
		while (--i)
			kill(data->ph[i].pid, SIGKILL);
	}
	if (ft_clear_sem(data))
		return (1);
	return (0);
}

/*It takes one philo edge case, even philos must wait to eat, then the cycle
eat -> sleep -> think starts*/
void ft_routine(t_data *data, t_philo *ph)
{
	if (ph->id % 2 == 0)
		ft_usleep(15, data);
	if (pthread_create(&ph->thread, NULL, ft_monitor, ph) != 0)
	{
		printf(THREAD_ERR_1);
		return ;
	}
	if (data->ph_nb == 1)
	{
		ft_one_philo(data, ph);
		return;
	}
	while (!ft_is_dead(data))
	{
		ft_eat(data, ph);
		printf("coucou\n");
		if (ft_is_finished(data))
		{
			if (pthread_join(ph->thread, NULL) != 0)
			{
				printf(THREAD_ERR_2);
				return ;
			}
			ft_clear_sem(data);
			exit(1);
		}
		ft_display(data, ph, 'S');
		ft_usleep(data->t_sleep, data);
		ft_display(data, ph, 'T');
		usleep(100);
	}
	if (pthread_join(ph->thread, NULL) != 0)
	{
		printf(THREAD_ERR_2);
		return ;
	}
	ft_clear_sem(data);
	exit (2);
}

/*Makes sure that philo stops after one dies, and checks the total number of
meals eaten*/
void *ft_monitor(void *arg)
{
	t_philo	*ph;
	int i;
	
	ph = (t_philo *)arg;
	while (!ft_is_finished(ph->data))
	{
		i = -1;
		while (++i < ph->data->ph_nb && !ft_is_dead(ph->data))
		{
			sem_wait(ph->data->meal);
			if (ft_get_time() - ph[i].t_last_meal >= ph->data->t_die)
				ft_set_death(ph->data, ph);
			sem_post(ph->data->meal);
			usleep(10);
		}
		if (ph->data->is_dead)
			return (NULL);
		i = 0;
		while (i < ph->data->ph_nb && ph->data->meal_nb != -1 && ft_meal_counter(ph->data, ph[i]) >= ph->data->meal_nb)
			i++;
		if (i == ph->data->ph_nb)
			ft_set_end(ph->data, ph);
	}
	return (NULL);
}

/*It displays its own death*/
void ft_one_philo(t_data *data, t_philo *ph)
{
	sem_wait(data->forks);
	ft_display(data, ph, 'F');
	sem_wait(data->forks);
	ft_usleep(data->t_die, data);
	ft_display(data, ph, 'D');
}

/*Properly destroys all the mutex and free the fork and philo arrays*/
int ft_clear_sem(t_data *data)
{
	if (sem_close(data->forks) == -1)
		return (printf(SEM_CLOSE), 1);
	if (sem_close(data->meal) == -1)
		return (printf(SEM_CLOSE), 1);
	if (sem_close(data->dead) == -1)
		return (printf(SEM_CLOSE), 1);
	if (sem_close(data->write) == -1)
		return (printf(SEM_CLOSE), 1);
	if (sem_close(data->monitor) == -1)
		return (printf(SEM_CLOSE), 1);
	sem_unlink("forks");
	sem_unlink("meal");
	sem_unlink("dead");
	sem_unlink("write");
	sem_unlink("monitor");
	free(data->ph);
	return (0);
}
