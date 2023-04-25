/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:11:34 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/26 08:04:14 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	try_to_eat(t_human *hum, struct timeval *last_time, int flag)
{
	while (1)
	{
		pthread_mutex_lock(&hum->res->mutex);
		if (hum->name == hum->arr[number_of_philosophers])
			if (grab_fork_max(hum, last_time) == fail)
				return (fail);
		if (hum->name != hum->arr[number_of_philosophers])
			if (grab_fork_novice(hum, last_time) == fail)
				return (fail);
		if (check_dead_or_ate(hum, last_time, no_print) == NULL)
			return (fail);
		if (check_both_hands(hum, flag) == success && hum->flag == 2)
		{
			if (eat(hum, last_time, flag) == fail)
				return (fail);
			else
				break ;
		}
		usleep(500);
	}
	return (success);
}

void	if_odd(t_human *hum, struct timeval *last_time)
{
	int	flag;

	pthread_mutex_lock(&hum->res->mutex);
	if (hum->name == hum->arr[number_of_philosophers])
		flag = max;
	else
		flag = novice;
	pthread_mutex_unlock(&hum->res->mutex);
	while (1)
	{
		if (try_to_eat(hum, last_time, flag) == fail)
			return ;
		if (check_dead_or_ate(hum, last_time, no_print) == NULL)
			return ;
		if (ssleep(hum, last_time) == fail)
			return ;
		if (check_dead_or_ate(hum, last_time, no_print) == NULL)
			return ;
		if (check_dead_or_ate(hum, last_time, thinking) == NULL)
			return ;
	}
}

void	if_even(t_human *hum, struct timeval *last_time)
{
	int	flag;

	pthread_mutex_lock(&hum->res->mutex);
	if (hum->name == hum->arr[number_of_philosophers])
		flag = max;
	else
		flag = novice;
	pthread_mutex_unlock(&hum->res->mutex);
	while (1)
	{
		if (try_to_eat(hum, last_time, flag) == fail)
			return ;
		if (check_dead_or_ate(hum, last_time, no_print) == NULL)
			return ;
		if (ssleep(hum, last_time) == fail)
			return ;
		if (check_dead_or_ate(hum, last_time, no_print) == NULL)
			return ;
		if (check_dead_or_ate(hum, last_time, thinking) == NULL)
			return ;
	}
}

void	grab_fork_and_die(t_human *hum)
{
	pthread_mutex_lock(hum->res->mfork);
	hum->res->forks[0] = 1;
	printf("%d %d has taken a fork\n", \
		timestamp(hum, hum->res->time), hum->name);
	pthread_mutex_unlock(hum->res->mfork);
	usleep_split(hum, hum->res->time, time_to_die, 0);
	pthread_mutex_lock(hum->res->mfork);
	printf("%d %d died\n", timestamp(hum, hum->res->time), hum->name);
	hum->res->tomb[0] = 1;
	pthread_mutex_unlock(hum->res->mfork);
}

void	*internal_f(void *arg)
{
	t_human			*hum;
	struct timeval	last_time;

	hum = (t_human *)arg;
	gettimeofday(&last_time, NULL);
	if (hum->arr[number_of_philosophers] == 1)
		grab_fork_and_die(hum);
	else if (hum->name % 2 == 1)
	{
		usleep(1000);
		if_odd(hum, &last_time);
	}
	else
		if_even(hum, &last_time);
	return (NULL);
}
