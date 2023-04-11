/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_making.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:11:34 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/12 04:17:03 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	timestamp(struct timeval time)
{
	struct timeval time1;

	gettimeofday(&time1, NULL);
	return ((int)((time1.tv_sec * 1000) - (time.tv_sec * 1000) + 
			(time1.tv_usec / 1000) - (time.tv_usec / 1000)));
}

void	usleep_split(t_human *hum, struct timeval time, int flag, int flag1)
{

	if (flag1 == 0)
		gettimeofday(&time, NULL);
	while (1)
	{
		if (timestamp(time) >= hum->arr[flag])
			return;
		usleep(50);
	}
}

t_human	*check_dead_or_ate(t_human *hum, struct timeval *last_time)
{
	static int	flag;

	pthread_mutex_lock(&hum->res->mutex1);
	pthread_mutex_lock(&hum->res->mutex);
	if ((hum->arr[must_eat] != -1 && hum->res->count / \
		hum->arr[number_of_philosophers] == hum->arr[must_eat]) \
		|| flag == 1)
	{
		if (flag == 0)
		{
			flag = 1;
			printf("%d %d is eating\n", timestamp(hum->res->time), hum->name);
		}
		hum->res->tomb[hum->name - 1] = 1;
		pthread_mutex_unlock(&hum->res->mutex);
		pthread_mutex_unlock(&hum->res->mutex1);
		usleep_split(hum, *last_time, time_to_eat, 0);
		return (NULL);
	}
	if (timestamp(*last_time) > hum->arr[time_to_die] || hum->res->dead_flag == 1) // 수상함
	{
		if (hum->res->dead_flag == 0)
			printf("%d %d died\n", timestamp(hum->res->time), hum->name);
		hum->res->dead_flag = 1;
		hum->res->tomb[hum->name - 1] = 1;
		pthread_mutex_unlock(&hum->res->mutex);
		pthread_mutex_unlock(&hum->res->mutex1);
		return (NULL);
	}
	pthread_mutex_unlock(&hum->res->mutex);
	pthread_mutex_unlock(&hum->res->mutex1);
	return (hum);
}

/*
esesest / e
ststste / s
tetetes / t
*/
/*
void	usleep_split(t_human *hum, int flag)
{
	int	sleep;
	int	temp;

	sleep = 50;
	temp = 0;
	while (hum->arr[flag] * 1000 >= temp)
	{
		usleep(sleep);
		temp = temp + sleep;
	}
}
*/
//이런 식의 잘라내기는 아무 의미가 없다.
//사실 잘라내는 이유가 실제 시간과 맞는지 아닌지 확인하기 위해 gettimeofday
//따위의 실제시간을 구하는 함수를 사용해서 실제 시간과 얼추 맞는 순간에 끊는
//거니까...
//일단은 usleep을 정직하게 줘 볼 생각이다.

t_human	*eat(t_human *hum, struct timeval *last_time)
{
	pthread_mutex_lock(&hum->res->mutex);
	hum->ate_numb ++;
	if (hum->ate_numb == hum->arr[must_eat])
		hum->res->count = hum->res->count + hum->ate_numb;
	pthread_mutex_unlock(&hum->res->mutex);
	if (check_dead_or_ate(hum, last_time) != NULL)
		printf("%d %d is eating\n", timestamp(hum->res->time), hum->name);
	else
		return (NULL);
	gettimeofday(last_time, NULL);
	usleep_split(hum, *last_time, time_to_eat, 1);
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
	if (check_dead_or_ate(hum, last_time) != NULL)
		printf("%d %d is sleeping\n", timestamp(hum->res->time), hum->name);
	else
		return (NULL);
	usleep_split(hum, *last_time, time_to_sleep, 0);
	return (hum);
}

void	usleep_split1(int time)
{
	int	temp;

	temp = 50;
	while (1)
	{
		if (time >= temp)
			return;
		usleep(50);
		temp = temp + 50;
	}
}

t_human	*think(t_human *hum, struct timeval *last_time)
{
	int	flag;

	flag = 0;
	if (check_dead_or_ate(hum, last_time) != NULL)
		printf("%d %d is thinking\n", timestamp(hum->res->time), hum->name);
	else
		return (NULL);
	usleep_split1(1500);
	while (1)
	{
		pthread_mutex_lock(&hum->res->mutex);
		if (hum->name == hum->arr[number_of_philosophers])
		{
			if (hum->res->forks[0] == 0 && hum->res->forks[hum->name - 1] == 0 && flag == 0)
			{
				hum->res->forks[0] = 1;
				hum->res->forks[hum->name - 1] = 1;
				pthread_mutex_unlock(&hum->res->mutex);
				flag ++;
				if (check_dead_or_ate(hum, last_time) != NULL)
					printf("%d %d has taken a fork\n", timestamp(hum->res->time), hum->name);
				else
					return (NULL);
				if (check_dead_or_ate(hum, last_time) != NULL)
					printf("%d %d has taken a fork\n", timestamp(hum->res->time), hum->name);
				else
					return (NULL);
			}
			pthread_mutex_unlock(&hum->res->mutex);
		}
		else
		{
			if (hum->res->forks[hum->name] == 0 && hum->res->forks[hum->name - 1] == 0 && flag == 0)
			{
				hum->res->forks[hum->name] = 1;
				hum->res->forks[hum->name - 1] = 1;
				pthread_mutex_unlock(&hum->res->mutex);
				flag ++;
				if (check_dead_or_ate(hum, last_time) != NULL)
					printf("%d %d has taken a fork\n", timestamp(hum->res->time), hum->name);
				else
					return (NULL);
				if (check_dead_or_ate(hum, last_time) != NULL)
					printf("%d %d has taken a fork\n", timestamp(hum->res->time), hum->name);
				else
					return (NULL);
			}
			pthread_mutex_unlock(&hum->res->mutex);
		}
		if (check_dead_or_ate(hum, last_time) == NULL)
			return (NULL);
		pthread_mutex_lock(&hum->res->mutex);
		if (hum->name == hum->arr[number_of_philosophers])
		{
			if (flag == 1)
				break ;
		}
		else
		{
			if (flag == 1)
				break ;
		}
		pthread_mutex_unlock(&hum->res->mutex);
	}
	pthread_mutex_unlock(&hum->res->mutex);
	return (hum);
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
		{
			pthread_mutex_unlock(&hum->res->mutex);
			return ;
		}
		if (ssleep(hum, &last_time) == NULL)
			return ;
	}
}

void	*internal_f(void *arg)
{
	t_human			*hum;

	hum = (t_human *)arg;
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
		hum[idx].ate_numb = 0;
		pthread_create(*thread + idx, NULL, internal_f, hum + idx);
		idx ++;
	}
	return (0);
}
