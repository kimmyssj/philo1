/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_to_eat1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:11:34 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/26 09:19:56 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_novice_hand(t_human *hum)
{
	if (hum->res->forks[hum->name] == 1)
	{
		pthread_mutex_unlock(hum->res->mfork + hum->name);
		return (e_success);
	}
	else
		pthread_mutex_unlock(hum->res->mfork + hum->name);
	return (e_fail);
}

int	check_both_hands(t_human *hum, int flag)
{
	pthread_mutex_lock(hum->res->mfork + hum->name - 1);
	if (hum->res->forks[hum->name - 1] == 1)
	{
		pthread_mutex_unlock(hum->res->mfork + hum->name - 1);
		if (flag == e_novice)
		{
			pthread_mutex_lock(hum->res->mfork + hum->name);
			if (check_novice_hand(hum) == e_success)
				return (e_success);
		}
		else
		{
			pthread_mutex_lock(hum->res->mfork);
			if (hum->res->forks[0] == 1)
			{
				pthread_mutex_unlock(hum->res->mfork);
				return (e_success);
			}
			else
				pthread_mutex_unlock(hum->res->mfork);
		}
	}
	else
		pthread_mutex_unlock(hum->res->mfork + hum->name - 1);
	return (e_fail);
}

void	let_it_go(t_human *hum, int flag)
{
	if (flag == e_max)
	{
		pthread_mutex_lock(hum->res->mfork);
		hum->res->forks[0] = 0;
		pthread_mutex_unlock(hum->res->mfork);
		pthread_mutex_lock(hum->res->mfork + hum->name - 1);
		hum->res->forks[hum->name - 1] = 0;
		pthread_mutex_unlock(hum->res->mfork + hum->name - 1);
	}
	else
	{
		pthread_mutex_lock(hum->res->mfork + hum->name);
		hum->res->forks[hum->name] = 0;
		pthread_mutex_unlock(hum->res->mfork + hum->name);
		pthread_mutex_lock(hum->res->mfork + hum->name - 1);
		hum->res->forks[hum->name - 1] = 0;
		pthread_mutex_unlock(hum->res->mfork + hum->name - 1);
	}
}

int	eat(t_human *hum, struct timeval *last_time, int flag)
{
	if (check_dead_or_ate(hum, last_time, e_eating) == NULL)
		return (e_fail);
	pthread_mutex_lock(&hum->res->mutex);
	hum->ate_numb ++;
	if (hum->ate_numb == hum->arr[e_must_eat])
		hum->res->count = hum->res->count + hum->ate_numb;
	pthread_mutex_unlock(&hum->res->mutex);
	gettimeofday(last_time, NULL);
	usleep_split(hum, *last_time, e_time_to_eat, 0);
	let_it_go(hum, flag);
	hum->flag = 0;
	return (e_success);
}
