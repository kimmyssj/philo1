/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_making_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:11:34 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/26 09:17:02 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	timestamp(t_human *hum, struct timeval time)
{
	struct timeval	time1;

	(void)hum;
	gettimeofday(&time1, NULL);
	return (time1.tv_sec * 1000 - time.tv_sec * 1000 + \
		time1.tv_usec / 1000 - time.tv_usec / 1000);
}

void	usleep_split(t_human *hum, struct timeval time, int flag, int flag1)
{
	int	resttime;

	if (hum->arr[e_nbr_of_philosophers] > 5)
		resttime = 6 * hum->arr[e_nbr_of_philosophers];
	else
		resttime = 30;
	if (flag1 == 0)
		gettimeofday(&time, NULL);
	while (1)
	{
		usleep(resttime);
		pthread_mutex_lock(&hum->res->mutex);
		if (timestamp(hum, time) >= hum->arr[flag])
			break ;
		pthread_mutex_unlock(&hum->res->mutex);
	}
	pthread_mutex_unlock(&hum->res->mutex);
}

void	print_in_mutex(t_human *hum, int flag)
{
	if (flag == e_grabfork)
		printf("%d %d has taken a fork\n", \
		timestamp(hum, hum->res->time), hum->name);
	else if (flag == e_eating)
		printf("%d %d is eating\n", timestamp(hum, hum->res->time), hum->name);
	else if (flag == e_thinking)
		printf("%d %d is thinking\n", timestamp(hum, hum->res->time), hum->name);
	else if (flag == e_sleeping)
		printf("%d %d is sleeping\n", timestamp(hum, hum->res->time), hum->name);
	return ;
}

pthread_mutex_t	*fork_mutex_maker(int hum_num)
{
	pthread_mutex_t	*forks;
	int				idx;

	forks = malloc(sizeof(pthread_mutex_t) * hum_num);
	if (forks == NULL)
		return (NULL);
	idx = 0;
	while (idx < hum_num)
	{
		pthread_mutex_init(forks + idx, NULL);
		idx ++;
	}
	return (forks);
}

t_human	*if_failed(t_resource **res, t_human **hum)
{
	free(*hum);
	free((*res)->forks);
	free((*res)->tomb);
	free(*res);
	return (NULL);
}
