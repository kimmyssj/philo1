/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tomb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:18:36 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/07 11:42:01 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_tomb(t_resource *res, int *array, pthread_t *threads)
{
	int	idx;

	idx = 0;
	while (idx < array[number_of_philosophers])
	{
		pthread_join(threads[idx], NULL);
		idx ++;
	}
	while (1)
	{
		if (res->dead_flag == 1)
			return ;
	}
}
