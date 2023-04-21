/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eatsleepthinkorder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:11:34 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/21 04:02:48 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_human	*think_eat_sleep(t_human *hum, struct timeval *last_time)
{
	gettimeofday(&hum->time, NULL);
	if (think(hum, last_time) == NULL)
		return (NULL);
	gettimeofday(&hum->time, NULL);
	if (eat(hum, last_time) == NULL)
	{
		pthread_mutex_unlock(&hum->res->mutex);
		return (NULL);
	}
	gettimeofday(&hum->time, NULL);
	if (ssleep(hum, last_time) == NULL)
		return (NULL);
	return (hum);
}

t_human	*eat_sleep_think(t_human *hum, struct timeval *last_time)
{
	gettimeofday(&hum->time, NULL);
	if (eat(hum, last_time) == NULL)
	{
		pthread_mutex_unlock(&hum->res->mutex);
		return (NULL);
	}
	gettimeofday(&hum->time, NULL);
	if (ssleep(hum, last_time) == NULL)
		return (NULL);
	gettimeofday(&hum->time, NULL);
	if (think(hum, last_time) == NULL)
		return (NULL);
	return (hum);
}

t_human	*sleep_think_eat(t_human *hum, struct timeval *last_time)
{
	gettimeofday(&hum->time, NULL);
	if (ssleep(hum, last_time) == NULL)
		return (NULL);
	gettimeofday(&hum->time, NULL);
	if (think(hum, last_time) == NULL)
		return (NULL);
	gettimeofday(&hum->time, NULL);
	if (eat(hum, last_time) == NULL)
	{
		pthread_mutex_unlock(&hum->res->mutex);
		return (NULL);
	}
	return (hum);
}
