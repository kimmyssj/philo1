/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_to_eat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:11:34 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/26 09:18:00 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	grab_fork_novice(t_human *hum, struct timeval *last_time)
{
	pthread_mutex_unlock(&hum->res->mutex);
	pthread_mutex_lock(hum->res->mfork + hum->name);
	if (hum->res->forks[hum->name] == 0)
	{
		hum->res->forks[hum->name] = 1;
		pthread_mutex_unlock(hum->res->mfork + hum->name);
		hum->flag ++;
		if (check_dead_or_ate(hum, last_time, e_grabfork) == NULL)
			return (e_fail);
	}
	else
		pthread_mutex_unlock(hum->res->mfork + hum->name);
	pthread_mutex_lock(hum->res->mfork + hum->name - 1);
	if (hum->res->forks[hum->name - 1] == 0)
	{
		hum->res->forks[hum->name - 1] = 1;
		pthread_mutex_unlock(hum->res->mfork + hum->name - 1);
		hum->flag ++;
		if (check_dead_or_ate(hum, last_time, e_grabfork) == NULL)
			return (e_fail);
	}
	else
		pthread_mutex_unlock(hum->res->mfork + hum->name - 1);
	return (e_success);
}

int	grab_fork_max(t_human *hum, struct timeval *last_time)
{
	pthread_mutex_unlock(&hum->res->mutex);
	pthread_mutex_lock(hum->res->mfork);
	if (hum->res->forks[0] == 0)
	{
		hum->res->forks[0] = 1;
		pthread_mutex_unlock(hum->res->mfork);
		hum->flag ++;
		if (check_dead_or_ate(hum, last_time, e_grabfork) == NULL)
			return (e_fail);
	}
	else
		pthread_mutex_unlock(hum->res->mfork);
	pthread_mutex_lock(hum->res->mfork + hum->name - 1);
	if (hum->res->forks[hum->name - 1] == 0)
	{
		hum->res->forks[hum->name - 1] = 1;
		pthread_mutex_unlock(hum->res->mfork + hum->name - 1);
		hum->flag ++;
		if (check_dead_or_ate(hum, last_time, e_grabfork) == NULL)
			return (e_fail);
	}
	else
		pthread_mutex_unlock(hum->res->mfork + hum->name - 1);
	return (e_success);
}
