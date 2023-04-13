/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_making.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:11:34 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/14 07:44:21 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	if_odd(t_human *hum, struct timeval *last_time)
{
	while (hum->name == hum->arr[number_of_philosophers])
	{
		if (think_eat_sleep(hum, last_time) == NULL)
			return ;
	}
	while (hum->name % 2 == 0)
	{
		if (eat_sleep_think(hum, last_time) == NULL)
			return ;
	}
	while (hum->name % 2 == 1)
	{
		if (sleep_think_eat(hum, last_time) == NULL)
			return ;
	}
}

void	if_even(t_human *hum, struct timeval *last_time)
{
	while (hum->name % 2 == 0)
	{
		if (eat_sleep_think(hum, last_time) == NULL)
			return ;
	}
	while (hum->name % 2 == 1)
	{
		if (sleep_think_eat(hum, last_time) == NULL)
			return ;
	}
}

void	grab_fork_and_die(t_human *hum)
{
	pthread_mutex_lock(&hum->res->mutex);
	hum->res->forks[0] = 1;
	printf("%d %d has taken a fork\n", timestamp(hum->res->time), hum->name);
	pthread_mutex_unlock(&hum->res->mutex);
	usleep_split(hum, hum->res->time, time_to_die, 0);
	pthread_mutex_lock(&hum->res->mutex);
	printf("%d %d died\n", timestamp(hum->res->time), hum->name);
	hum->res->tomb[0] = 1;
	pthread_mutex_unlock(&hum->res->mutex);
}

void	*internal_f(void *arg)
{
	t_human			*hum;
	struct timeval	last_time;

	hum = (t_human *)arg;
	pthread_mutex_lock(&hum->res->mutex);
	hum->res->start_line ++;
	pthread_mutex_unlock(&hum->res->mutex);
	while (1)
	{
		pthread_mutex_lock(&hum->res->mutex);
		gettimeofday(&hum->res->time, NULL);
		gettimeofday(&last_time, NULL);
		if (hum->res->start_line == hum->arr[number_of_philosophers])
			break ;
		pthread_mutex_unlock(&hum->res->mutex);
	}
	pthread_mutex_unlock(&hum->res->mutex);
	if (hum->arr[number_of_philosophers] == 1)
		grab_fork_and_die(hum);
	else if (hum->arr[number_of_philosophers] % 2 == 1)
		if_odd(hum, &last_time);
	else
		if_even(hum, &last_time);
	return (NULL);
}

t_human	*create_philo(t_resource *res, int *arr, pthread_t **thread)
{
	t_human	*hum;
	int		idx;

	hum = malloc(sizeof(t_human) * arr[number_of_philosophers]);
	if (hum == NULL)
	{
		free_all1(&res->forks, &res->tomb, NULL);
		free(res);
		return (NULL);
	}
	pthread_mutex_init(&res->mutex, NULL);
	idx = 0;
	while (idx < arr[number_of_philosophers])
	{
		hum[idx].res = res;
		hum[idx].arr = arr;
		hum[idx].name = idx + 1;
		hum[idx].ate_numb = 0;
		pthread_create(*thread + idx, NULL, internal_f, hum + idx);
		idx ++;
	}
	return (hum);
}
