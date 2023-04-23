/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:11:34 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/23 20:40:05 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	else_empty(t_human *hum, int flag)
{
	pthread_mutex_unlock(&hum->res->mutex);
	pthread_mutex_lock(hum->res->mfork + hum->name);
	if (flag == 0 && hum->res->forks[hum->name] == 0)
	{
		pthread_mutex_unlock(hum->res->mfork + hum->name);
		pthread_mutex_lock(hum->res->mfork + hum->name - 1);
		if (hum->res->forks[hum->name - 1] == 0)
			flag ++;
		pthread_mutex_unlock(hum->res->mfork + hum->name - 1);
	}
	else
		pthread_mutex_unlock(hum->res->mfork + hum->name);
	return (flag);
}

int	is_fork_empty(t_human *hum, int flag)
{
	pthread_mutex_lock(&hum->res->mutex);
	if (hum->name == hum->arr[number_of_philosophers])
	{
		pthread_mutex_unlock(&hum->res->mutex);
		pthread_mutex_lock(hum->res->mfork);
		if (flag == 0 && hum->res->forks[0] == 0)
		{
			pthread_mutex_unlock(hum->res->mfork);
			pthread_mutex_lock(hum->res->mfork + hum->name - 1);
			if (hum->res->forks[hum->name - 1] == 0)
				flag ++;
			pthread_mutex_unlock(hum->res->mfork + hum->name - 1);
		}
		else
			pthread_mutex_unlock(hum->res->mfork);
	}
	else
		flag = else_empty(hum, flag);
	return (flag);
}

t_human	*think(t_human *hum, struct timeval *last_time)
{
	int	flag;

	flag = 0;
	usleep(300);
	if (check_dead_or_ate(hum, last_time, thinking) == NULL)
		return (NULL);
	while (flag == 0)
	{
		flag = is_fork_empty(hum, flag);
		if (check_dead_or_ate(hum, last_time, no_print) == NULL)
			return (NULL);
	}
	return (hum);
}
