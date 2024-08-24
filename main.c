/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:46:57 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/24 21:18:27 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Parsing and initialitazion of two structs, then it starts the simulation*/
int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (ft_data_init(&data, av))
			return (1);
		if (ft_philo_init(&data))
			return (1);
		if (ft_simulation(&data))
			return (1);
	}
	else
		return (printf(ARG_ERR), 1);
	return (0);
}
