/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_making_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:11:34 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/14 06:51:41 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	timestamp(struct timeval time)
{
	struct timeval	time1;

	gettimeofday(&time1, NULL);
	return ((time1.tv_sec - time.tv_sec) * 1000 + \
		(time1.tv_usec - time.tv_usec) / 1000);
}

void	usleep_split(t_human *hum, struct timeval time, int flag, int flag1)
{
	int	rest_time;

	rest_time = 20 * hum->arr[number_of_philosophers];
	if (flag1 == 0)
		gettimeofday(&time, NULL);
	while (1)
	{
		usleep(rest_time);
		pthread_mutex_lock(&hum->res->mutex);
		if (timestamp(time) >= hum->arr[flag])
		{
			pthread_mutex_unlock(&hum->res->mutex);
			return ;
		}
		pthread_mutex_unlock(&hum->res->mutex);
	}
}

void	print_in_mutex(t_human *hum, int flag)
{
	if (flag == grabfork)
		printf("%d %d has taken a fork\n", timestamp(hum->res->time), hum->name);
	else if (flag == eating)
		printf("%d %d is eating\n", timestamp(hum->res->time), hum->name);
	else if (flag == thinking)
		printf("%d %d is thinking\n", timestamp(hum->res->time), hum->name);
	else if (flag == sleeping)
		printf("%d %d is sleeping\n", timestamp(hum->res->time), hum->name);
	return ;
}
