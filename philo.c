/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:46:57 by pajimene          #+#    #+#             */
/*   Updated: 2024/06/26 19:55:06 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	
	if (ac != 5)
	{
		printf(ARG_ERR);
		return (1);
	}
	if (ft_parse_input(&data, av))
	{
		printf(SYNTAX_ERR);
		return (1);
	}
	//ft_data_init(&data);
	//ft_simulation(&data);
	return (0);
}