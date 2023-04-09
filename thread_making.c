/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_making.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:11:34 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/10 00:51:08 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	tmake(struct timeval time)
{
	struct timeval time1;

	gettimeofday(&time1, NULL);
	return ((int)((time1.tv_sec * 1000) - (time.tv_sec * 1000) + 
			(time1.tv_usec / 1000) - (time.tv_usec / 1000)));
}

t_human	*check_dead_or_ate(t_human *hum, int hunger_time)
{
	pthread_mutex_lock(&hum->res->mutex1);
	if (hum->arr[must_eat] != -1 && hum->res->count / hum->arr[number_of_philosophers] == 1)
		return (NULL);
	pthread_mutex_unlock(&hum->res->mutex1);
	if (hunger_time > hum->arr[time_to_die] * 1000 || hum->res->dead_flag == 1) // 수상함
	{
		pthread_mutex_lock(&hum->res->mutex1);
		if (hum->res->dead_flag == 0)
			printf("%d %d died\n", tmake(hum->res->time), hum->name);
		hum->res->dead_flag = 1;
		hum->res->tomb[hum->name - 1] = 1;
		pthread_mutex_unlock(&hum->res->mutex1);
		return (NULL);
	}
	return (hum);
}

/*
esesest / e
ststste / s
tetetes / t
*/
void	usleep_split(t_human *hum, int flag)
{
	int	sleep;
	int	temp;

	sleep = 50;
	temp = 0;
	while (hum->arr[flag] * 1000 > temp)
	{
		usleep(sleep);
		temp = temp + sleep;
	}
}

t_human	*eat(t_human *hum, struct timeval *last_time)
{
	pthread_mutex_lock(&hum->res->mutex);
	if (hum->name == hum->arr[number_of_philosophers])
	{
		hum->res->forks[0] = 1;
		hum->res->forks[hum->name - 1] = 1;
		pthread_mutex_unlock(&hum->res->mutex);
		if (check_dead_or_ate(hum, tmake(*last_time)) != NULL)
			printf("%d %d has taken a fork\n", tmake(hum->res->time), hum->name);
		else
			return (NULL);
		if (check_dead_or_ate(hum, tmake(*last_time)) != NULL)
			printf("%d %d has taken a fork\n", tmake(hum->res->time), hum->name);
		else
			return (NULL);
	}
	else
	{
		hum->res->forks[hum->name] = 1;
		hum->res->forks[hum->name - 1] = 1;
		pthread_mutex_unlock(&hum->res->mutex);
		if (check_dead_or_ate(hum, tmake(*last_time)) != NULL)
			printf("%d %d has taken a fork\n", tmake(hum->res->time), hum->name);
		else
			return (NULL);
		if (check_dead_or_ate(hum, tmake(*last_time)) != NULL)
			printf("%d %d has taken a fork\n", tmake(hum->res->time), hum->name);
		else
			return (NULL);
	}
	if (check_dead_or_ate(hum, tmake(*last_time)) != NULL)
		printf("%d %d is eating\n", tmake(hum->res->time), hum->name);
	else
		return (NULL);
	gettimeofday(last_time, NULL);
	usleep_split(hum, time_to_eat);
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

t_human	*ssleep(t_human *hum, struct timeval *last_time)
{
	if (check_dead_or_ate(hum, tmake(*last_time)) != NULL)
		printf("%d %d is sleeping\n", tmake(hum->res->time), hum->name);
	else
		return (NULL);
	usleep_split(hum, time_to_sleep);
	return (hum);
}

t_human	*check_think(t_human *hum, int flag)
{
	int	flag1;

	flag1 = 0;
	if (flag == hum->arr[number_of_philosophers])
	{
		if (hum->res->forks[hum->name - 1] == 0 && \
			hum->res->forks[0] == 0)
			flag1 = 1;
	}
	else
	{
		if (hum->res->forks[hum->name - 1] == 0 && \
			hum->res->forks[hum->name] == 0)
			flag1 = 1;
	}	
	pthread_mutex_unlock(&hum->res->mutex);
	if (flag1 == 0)
		return (NULL);
	else
		return (hum);
}

t_human	*think(t_human *hum, struct timeval *last_time)
{
	int	flag;

	flag = 0;
	if (check_dead_or_ate(hum, tmake(*last_time)) != NULL)
		printf("%d %d is thinking\n", tmake(hum->res->time), hum->name);
	else
		return (NULL);
	while (flag == 0)
	{
		pthread_mutex_lock(&hum->res->mutex);
		if (hum->name == hum->arr[number_of_philosophers])
		{
			if (hum->res->forks[hum->name - 1] == 0 && \
				hum->res->forks[0] == 0)
				flag = 1;
		}
		else
		{
			if (hum->res->forks[hum->name - 1] == 0 && \
				hum->res->forks[hum->name] == 0)
				flag = 1;
		}
		pthread_mutex_unlock(&hum->res->mutex);
	}
	return (hum);
}

void	eat_sleep(t_human *hum)
{
	struct timeval last_time;

	gettimeofday(&last_time, NULL);
	while (1)
	{
		if (eat(hum, &last_time) == NULL)
			return ;
		if (ssleep(hum, &last_time) == NULL)
			return ;
		if (think(hum, &last_time) == NULL)
			return ;
	}
}

void	eat_sleep_think(t_human *hum)
{
	struct timeval last_time;

	gettimeofday(&last_time, NULL);
	while (1)
	{
		if (think(hum, &last_time) == NULL)
			return ;
		if (eat(hum, &last_time) == NULL)
			return ;
		if (ssleep(hum, &last_time) == NULL)
			return ;
	}
}

void	*internal_f(void *arg)
{
	t_human			*hum;

	hum = (t_human *)arg;
	if (hum->arr[number_of_philosophers] / 2 == 0) // even
		eat_sleep(hum);
	else										   // odd
		eat_sleep_think(hum);
	return (NULL);
}

int	create_philo(t_resource *res, int *arr, pthread_t **thread)
{
	t_human	*hum;
	int		idx;

	hum = malloc(sizeof(t_human) * arr[number_of_philosophers]);
	if (hum == NULL)
	{
		free_all1(&res->forks, &res->tomb, NULL); // 추후에 전부 free해주는 걸 만들자 뮤텍스조차
		free(res);
		return (1);
	}
	pthread_mutex_init(&res->mutex, NULL);
	pthread_mutex_init(&res->mutex1, NULL);
	pthread_mutex_init(&res->mutex2, NULL);
	idx = 0;
	while (idx < arr[number_of_philosophers])
	{
		hum[idx].res = res;
		hum[idx].arr = arr;
		hum[idx].name = idx + 1;
		pthread_create(*thread + idx, NULL, internal_f, hum + idx);
		idx ++;
	}
	return (0);
}
