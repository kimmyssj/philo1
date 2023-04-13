/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:11:34 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/14 07:20:17 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_human	*grab_fork(t_human *hum, struct timeval *last_time)
{
	if (hum->name == hum->arr[number_of_philosophers])
	{
		hum->res->forks[0] = 1;
		pthread_mutex_unlock(&hum->res->mutex);
		if (check_dead_or_ate(hum, last_time, grabfork) == NULL)
			return (NULL);
		pthread_mutex_lock(&hum->res->mutex);
		hum->res->forks[hum->name - 1] = 1;
		pthread_mutex_unlock(&hum->res->mutex);
		if (check_dead_or_ate(hum, last_time, grabfork) == NULL)
			return (NULL);
	}
	else
	{
		hum->res->forks[hum->name] = 1;
		pthread_mutex_unlock(&hum->res->mutex);
		if (check_dead_or_ate(hum, last_time, grabfork) == NULL)
			return (NULL);
		pthread_mutex_lock(&hum->res->mutex);
		hum->res->forks[hum->name - 1] = 1;
		pthread_mutex_unlock(&hum->res->mutex);
		if (check_dead_or_ate(hum, last_time, grabfork) == NULL)
			return (NULL);
	}
	return (hum);
}

t_human	*eat(t_human *hum, struct timeval *last_time)
{
	pthread_mutex_lock(&hum->res->mutex);
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
	pthread_mutex_lock(&hum->res->mutex);
	if (hum->name == hum->arr[number_of_philosophers])
	{
		hum->res->forks[0] = 0;
		hum->res->forks[hum->name - 1] = 0;
	}
	else
	{
		hum->res->forks[hum->name] = 0;
		hum->res->forks[hum->name - 1] = 0;
	}
	pthread_mutex_unlock(&hum->res->mutex);
	return (hum);
}
