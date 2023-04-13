/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:11:34 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/14 07:40:18 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_fork_empty(t_human *hum, int flag)
{
	pthread_mutex_lock(&hum->res->mutex);
	if (hum->name == hum->arr[number_of_philosophers])
	{
		if (hum->res->forks[0] == 0 && \
			hum->res->forks[hum->name - 1] == 0 && flag == 0)
		{
			pthread_mutex_unlock(&hum->res->mutex);
			flag ++;
		}
		else
			pthread_mutex_unlock(&hum->res->mutex);
	}
	else
	{
		if (hum->res->forks[hum->name] == 0 && \
			hum->res->forks[hum->name - 1] == 0 && flag == 0)
		{
			pthread_mutex_unlock(&hum->res->mutex);
			flag ++;
		}
		else
			pthread_mutex_unlock(&hum->res->mutex);
	}
	return (flag);
}

t_human	*think(t_human *hum, struct timeval *last_time)
{
	int	flag;

	flag = 0;
	if (check_dead_or_ate(hum, last_time, thinking) == NULL)
		return (NULL);
	usleep(400);
	while (flag == 0)
	{
		flag = is_fork_empty(hum, flag);
		if (check_dead_or_ate(hum, last_time, no_print) == NULL)
			return (NULL);
	}
	return (hum);
}
