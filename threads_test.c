/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:27:27 by pajimene          #+#    #+#             */
/*   Updated: 2024/06/28 18:14:54 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	*print_t1(void	*arg)
{
	int	i;
	(void)arg;

	i = 0;
	while (i++ < 1000)
	{
		printf("Thread n1 executing, YOLO!\n");
		usleep(1000);
	}
	return (NULL);
}

void	*print_t2(void	*arg)
{
	int	i;
	(void)arg;
	
	i = 0;
	while (i++ < 1000)
	{
		printf("Thread n2 executing, ACAB!\n");
		usleep(1000);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create(&t1, NULL, print_t1, NULL))
		exit(1);
	if (pthread_create(&t2, NULL, print_t2, NULL))
		exit(1);

	if (pthread_join(t1, NULL))
		exit(1);
	if (pthread_join(t2, NULL))
		exit(1);
	return (0);
}