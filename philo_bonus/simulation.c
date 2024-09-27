/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:37:33 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/27 11:44:34 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*It creates one process per philosopher, and each philo routine is
supervised by the monitor thread, each process has its own unique thread,
once one philo dies or they ate all the meals, the simulation ends properly*/
int	ft_simulation(t_data *data)
{
	int	i;
	int	status;

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
	while (--i)
		kill(data->ph[i].pid, SIGKILL);
	if (status == 256)
		printf(GREEN "%ld everyone finished their meal ! 🎉\n" RESET, \
			ft_get_time() - data->t_start + data->t_eat);
	if (ft_clear_sem(data))
		return (1);
	return (0);
}

/*Even philos start witha  little offset, then we launch a thread to monitor
the routine of the philo, it exits code is 1 if all the meals have be eaten, it
repeats the reoutine until on philo process dies or everyone have eaten*/
void	ft_routine(t_data *data, t_philo *ph)
{
	if (ph->id % 2 == 0)
		ft_usleep(15, data);
	if (pthread_create(&ph->thread, NULL, ft_monitor, ph) != 0)
		return ((void)printf(THREAD_ERR_1));
	if (data->ph_nb == 1)
		return (ft_one_philo(data, ph));
	while (!ft_is_dead(data))
	{
		if (ft_is_finished(data))
		{
			if (pthread_join(ph->thread, NULL) != 0)
				return ((void)printf(THREAD_ERR_2));
			ft_clear_sem(data);
			exit(1);
		}
		ft_eat_sleep_think(data, ph);
	}
	if (pthread_join(ph->thread, NULL) != 0)
		return ((void)printf(THREAD_ERR_2));
	ft_clear_sem(data);
	exit(2);
}

/*Makes sure that the process and thread stops after one dies, 
and checks the total number of meals eaten*/
void	*ft_monitor(void *arg)
{
	t_philo	*ph;
	long	time;

	ph = (t_philo *)arg;
	while (!ft_is_finished(ph->data))
	{
		sem_wait(ph->data->meal);
		time = ft_get_time() - ph->t_last_meal;
		sem_post(ph->data->meal);
		if (time >= ph->data->t_die)
		{
			if (!ft_is_dead(ph->data))
			{
				sem_post(ph->data->dead);
				sem_wait(ph->data->write);
				printf(RED "%ld %d died 💀\n" RESET, \
					ft_get_time() - ph->data->t_start, ph->id);
			}
			return (NULL);
			usleep(10);
		}
	}
	return (NULL);
}

/*It displays its own death and exits the process*/
void	ft_one_philo(t_data *data, t_philo *ph)
{
	sem_wait(data->forks);
	ft_display(data, ph, 'F');
	ft_usleep(data->t_die, data);
	ft_display(data, ph, 'D');
	if (pthread_join(ph->thread, NULL) != 0)
		return ((void)printf(THREAD_ERR_2));
	ft_clear_sem(data);
	exit(2);
}

/*Properly destroys all the semaphores and free the philo arrays*/
int	ft_clear_sem(t_data *data)
{
	if (sem_close(data->forks) == -1)
		return (printf(SEM_CLOSE), 1);
	if (sem_close(data->meal) == -1)
		return (printf(SEM_CLOSE), 1);
	if (sem_close(data->dead) == -1)
		return (printf(SEM_CLOSE), 1);
	if (sem_close(data->write) == -1)
		return (printf(SEM_CLOSE), 1);
	if (sem_close(data->meal_monitor) == -1)
		return (printf(SEM_CLOSE), 1);
	sem_unlink("forks");
	sem_unlink("meal");
	sem_unlink("dead");
	sem_unlink("write");
	sem_unlink("meal_monitor");
	free(data->ph);
	return (0);
}
