/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:11:34 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/26 09:42:38 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	try_to_eat(t_human *hum, struct timeval *last_time, int flag)
{
	while (1)
	{
		pthread_mutex_lock(&hum->res->mutex);
		if (hum->name == hum->arr[e_nbr_of_philosophers])
			if (grab_fork_max(hum, last_time) == e_fail)
				return (e_fail);
		if (hum->name != hum->arr[e_nbr_of_philosophers])
			if (grab_fork_novice(hum, last_time) == e_fail)
				return (e_fail);
		if (check_dead_or_ate(hum, last_time, e_no_print) == NULL)
			return (e_fail);
		if (check_both_hands(hum, flag) == e_success && hum->flag == 2)
		{
			if (eat(hum, last_time, flag) == e_fail)
				return (e_fail);
			else
				break ;
		}
		usleep(30);
	}
	return (e_success);
}

void	if_odd(t_human *hum, struct timeval *last_time)
{
	int	flag;

	pthread_mutex_lock(&hum->res->mutex);
	if (hum->name == hum->arr[e_nbr_of_philosophers])
		flag = e_max;
	else
		flag = e_novice;
	pthread_mutex_unlock(&hum->res->mutex);
	while (1)
	{
		if (try_to_eat(hum, last_time, flag) == e_fail)
			return ;
		if (check_dead_or_ate(hum, last_time, e_no_print) == NULL)
			return ;
		if (ssleep(hum, last_time) == e_fail)
			return ;
		if (check_dead_or_ate(hum, last_time, e_no_print) == NULL)
			return ;
		if (check_dead_or_ate(hum, last_time, e_thinking) == NULL)
			return ;
	}
}

void	if_even(t_human *hum, struct timeval *last_time)
{
	int	flag;

	pthread_mutex_lock(&hum->res->mutex);
	if (hum->name == hum->arr[e_nbr_of_philosophers])
		flag = e_max;
	else
		flag = e_novice;
	pthread_mutex_unlock(&hum->res->mutex);
	while (1)
	{
		if (try_to_eat(hum, last_time, flag) == e_fail)
			return ;
		if (check_dead_or_ate(hum, last_time, e_no_print) == NULL)
			return ;
		if (ssleep(hum, last_time) == e_fail)
			return ;
		if (check_dead_or_ate(hum, last_time, e_no_print) == NULL)
			return ;
		if (check_dead_or_ate(hum, last_time, e_thinking) == NULL)
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
	usleep_split(hum, hum->res->time, e_time_to_die, 0);
	pthread_mutex_lock(hum->res->mfork);
	printf("%d %d died\n", timestamp(hum, hum->res->time), hum->name);
	hum->res->tomb[0] = 1;
	pthread_mutex_unlock(hum->res->mfork);
}

void	*internal_f(void *arg)
{
	t_human			*hum;
	struct timeval	last_time;
	int				resttime;

	hum = (t_human *)arg;
	gettimeofday(&last_time, NULL);
	pthread_mutex_lock(&hum->res->mutex);
	resttime = 500 * hum->arr[e_nbr_of_philosophers];
	if (hum->arr[e_nbr_of_philosophers] == 1)
	{
		pthread_mutex_unlock(&hum->res->mutex);
		grab_fork_and_die(hum);
	}
	else
	{
		pthread_mutex_unlock(&hum->res->mutex);
		if (hum->name % 2 == 1)
		{
			usleep(resttime);
			if_odd(hum, &last_time);
		}
		else
			if_even(hum, &last_time);
	}
	return (NULL);
}
