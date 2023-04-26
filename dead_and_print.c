/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_and_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:11:34 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/26 09:23:39 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_human	*dead(t_human *hum, struct timeval *last_time)
{
	if (timestamp(hum, *last_time) >= hum->arr[e_time_to_die] \
		|| hum->res->dead_flag == 1)
	{
		if (hum->res->dead_flag == 0)
			printf("%d %d died\n", timestamp(hum, hum->res->time), hum->name);
		hum->res->dead_flag = 1;
		hum->res->tomb[hum->name - 1] = 1;
		pthread_mutex_unlock(&hum->res->mutex);
		return (NULL);
	}
	return (hum);
}

t_human	*check_dead_or_ate(t_human *hum, struct timeval *last_time, int flag1)
{
	static int		flag;

	pthread_mutex_lock(&hum->res->mutex);
	if ((hum->arr[e_must_eat] != -1 && hum->res->count / \
		hum->arr[e_nbr_of_philosophers] == hum->arr[e_must_eat]) \
		|| flag == 1)
	{
		if (flag == 0)
			flag = 1;
		hum->res->tomb[hum->name - 1] = 1;
		pthread_mutex_unlock(&hum->res->mutex);
		usleep_split(hum, *last_time, e_time_to_eat, 0);
		return (NULL);
	}
	if (dead(hum, last_time) == NULL)
		return (NULL);
	print_in_mutex(hum, flag1);
	pthread_mutex_unlock(&hum->res->mutex);
	return (hum);
}
