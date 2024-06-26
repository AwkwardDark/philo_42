/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:45:28 by pajimene          #+#    #+#             */
/*   Updated: 2024/06/26 19:55:52 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

# define ARG_ERR "\nWrong input, format must be: ./philo \
<number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>\n\n"
# define SYNTAX_ERR "\nThere's a syntax error, please enter only natural\
 numbers (miliseconds)\n\n"

typedef struct s_philo t_philo;

typedef struct s_fork{
	int				id;
	pthread_mutex_t	mutex;
}		t_fork;

typedef struct s_data{
	int		number;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	long	start_simulation_time;
	bool	end_simulation;
	t_fork	*forks;
	t_philo	*philos;
}		t_data;

typedef struct s_philo{
	int			id;
	pthread_t	thread_id;
	t_fork		*left_fork;
	t_fork		*right_fork;
	long		last_meal_time;
	t_data		*data;
}		t_philo;

//Cheking Errors and Parsing
int	ft_parse_input(t_data *data, char **av);

#endif