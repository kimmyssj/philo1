/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desroy_all_mutex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 00:00:25 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/22 00:04:14 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all_mutex(t_resource *res, int *arr)
{
	int	idx;

	idx = 0;
	pthread_mutex_destroy(&res->mutex);
	while (idx < arr[number_of_philosophers])
	{
		pthread_mutex_destroy(res->mfork + idx);
		idx ++;
	}
	free(res->mfork);
}
