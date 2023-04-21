/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:11:34 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/21 22:50:35 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_human	*when_nnbrofphi(t_human *hum, struct timeval *last_time)
{
	pthread_mutex_lock(hum->res->mfork + hum->name);
	hum->res->forks[hum->name] = 1;
	pthread_mutex_unlock(hum->res->mfork + hum->name);
	if (check_dead_or_ate(hum, last_time, grabfork) == NULL)
		return (NULL);
	pthread_mutex_lock(hum->res->mfork + hum->name - 1);
	hum->res->forks[hum->name - 1] = 1;
	pthread_mutex_unlock(hum->res->mfork + hum->name - 1);
	if (check_dead_or_ate(hum, last_time, grabfork) == NULL)
		return (NULL);
	return (hum);
}

t_human	*grab_fork(t_human *hum, struct timeval *last_time)
{
	if (hum->name == hum->arr[number_of_philosophers])
	{
		pthread_mutex_lock(hum->res->mfork);
		hum->res->forks[0] = 1;
		pthread_mutex_unlock(hum->res->mfork);
		if (check_dead_or_ate(hum, last_time, grabfork) == NULL)
			return (NULL);
		pthread_mutex_lock(hum->res->mfork + hum->name - 1);
		hum->res->forks[hum->name - 1] = 1;
		pthread_mutex_unlock(hum->res->mfork + hum->name - 1);
		if (check_dead_or_ate(hum, last_time, grabfork) == NULL)
			return (NULL);
	}
	else
		if (when_nnbrofphi(hum, last_time) == NULL)
			return (NULL);
	return (hum);
}

void	let_it_go(t_human *hum)
{
	pthread_mutex_lock(&hum->res->mutex);
	if (hum->name == hum->arr[number_of_philosophers])
	{
		pthread_mutex_unlock(&hum->res->mutex);
		pthread_mutex_lock(hum->res->mfork);
		hum->res->forks[0] = 0;
		pthread_mutex_unlock(hum->res->mfork);
		pthread_mutex_lock(hum->res->mfork + hum->name - 1);
		hum->res->forks[hum->name - 1] = 0;
		pthread_mutex_unlock(hum->res->mfork + hum->name - 1);
	}
	else
	{
		pthread_mutex_unlock(&hum->res->mutex);
		pthread_mutex_lock(hum->res->mfork + hum->name);
		hum->res->forks[hum->name] = 0;
		pthread_mutex_unlock(hum->res->mfork + hum->name);
		pthread_mutex_lock(hum->res->mfork + hum->name - 1);
		hum->res->forks[hum->name - 1] = 0;
		pthread_mutex_unlock(hum->res->mfork + hum->name - 1);
	}
}

t_human	*eat(t_human *hum, struct timeval *last_time)
{
	if (grab_fork(hum, last_time) == NULL)
		return (NULL);
	pthread_mutex_lock(&hum->res->mutex);
	hum->ate_numb ++;
	if (hum->ate_numb == hum->arr[must_eat])
		hum->res->count = hum->res->count + hum->ate_numb;
	pthread_mutex_unlock(&hum->res->mutex);
	if (check_dead_or_ate(hum, last_time, eating) == NULL)
		return (NULL);
	gettimeofday(last_time, NULL);
	usleep_split(hum, *last_time, time_to_eat, 0);
	let_it_go(hum);
	return (hum);
}
