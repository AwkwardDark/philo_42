/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:45:28 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/25 09:39:44 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

/*Color macros*/
# define BLUE "\033[0;34m"
# define RED "\033[0;31m"
# define G "\033[0;32m"
# define RESET "\033[0m"

/*Message error macros*/
# define ARG_ERR "\nWrong input, format must be: ./philo \
<number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>\
 [<nb_of_meals>]\n\n"
# define SYNTAX_ERR "\nThere's a syntax error, please enter only natural\
 numbers\n\n"
# define DATA_ERR "\nThere's a data error, number of philos must be between\
 1 and 200, and the number of meals and all times (in ms) greater than 0\n\n"
# define MALL_ERR "\nThere's a memory allocation error!\n\n"
# define MUTEX_ERR_1 "\nThere's a mutex allocation error!\n\n"
# define MUTEX_ERR_2 "\nThere's a mutex destruction error!\n\n"
# define THREAD_ERR_1 "\nThere's a thread allocation error!\n\n"
# define THREAD_ERR_2 "\nThere's a thread join error!\n\n"

typedef struct s_philo	t_philo;

/*Data struct is shared between all philosophers and it's used to monitor them
It has all the mutex, and the array of philos and forks (mutexes)*/
typedef struct s_data{
	int				ph_nb;
	int				meal_nb;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			t_start;
	int				is_dead;
	int				is_finished;
	t_philo			*ph;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	meal;
	pthread_mutex_t	dead;
	pthread_mutex_t	monitor;
}		t_data;

/*Each philo is a single thread, which points to the data struct also*/
typedef struct s_philo{
	pthread_t	thread;
	t_data		*data;
	int			id;
	int			r_fork;
	int			l_fork;
	int			meals_eaten;
	long		t_last_meal;
}		t_philo;

/*Cheking Errors, Parsing & Initialazing*/
int				ft_data_init(t_data *data, char **av);
int				ft_philo_init(t_data *data);

/*Threads, Mutex and Free fonctions*/
int				ft_init_mutex_data(t_data *data);
int				ft_clear_mutex(t_data *data);

/*Simulation, Monitor and Supervisor*/
int				ft_simulation(t_data *data);
void			ft_monitor(t_data *data, t_philo *ph);
void			*ft_routine(void *arg);
void			ft_one_philo(t_data *data, t_philo *ph);

/*Actions*/
void			ft_display(t_data *data, t_philo *ph, char c);
void			ft_eat(t_data *data, t_philo *ph);
int				ft_is_dead(t_data *data);
void			ft_set_death(t_data *data, t_philo *ph);
int				ft_is_finished(t_data *data);
int				ft_meal_counter(t_data *data, t_philo ph);
void			ft_set_end(t_data *data, t_philo *ph);

/*Utils*/
long			ft_get_time(void);
void			ft_usleep(long time, t_data *data);
long			ft_atol(char *str);
int				ft_check_syntax(char *str);

#endif