/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:46:51 by pajimene          #+#    #+#             */
/*   Updated: 2024/06/28 18:12:38 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_get_time(void)
{
	unsigned long	time;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((unsigned long)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

int	main(void)
{
	printf("Time is: %lu\n", ft_get_time());
	return (0);
}
