/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_making.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:11:34 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/07 11:47:13 by seungjki         ###   ########.fr       */
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
		pthread_mutex_unlock(&hum->res->mutex1);
		return (NULL);
	}
	return (hum);
}

int	grab_fork(t_human *hum, int last_time_eat, int *flag)
{
	*flag = 0;
	pthread_mutex_lock(&hum->res->mutex);
	if (hum->name == hum->arr[number_of_philosophers])
	{
		if (hum->res->forks[hum->name - 1] == 0)
		{
			hum->res->forks[0] = 1;
			*flag = 1;
		}
	}
	else
	{
		if (hum->res->forks[hum->name - 1] == 0)
		{
			hum->res->forks[hum->name] = 1;
			*flag = 1;
		}
	}
	if (check_dead_or_ate(hum, last_time_eat) == NULL)
	{
		pthread_mutex_unlock(&hum->res->mutex);
		return (0);
	}
	if (*flag == 1)
		if (check_dead_or_ate(hum, last_time_eat) != NULL)
			printf("%d %d has taken a fork\n", tmake(hum->res->time), hum->name);
	pthread_mutex_unlock(&hum->res->mutex);
	return (1);
}
// 좌측도 확인해 주어야 한다.
void	grab_eat_sleep(t_human *hum, struct timeval *last_time_eat)
{
	if (hum->res->forks[hum->name - 1] == 0)
		hum->res->forks[hum->name - 1] = 1;
	else
	{
		if (hum->name == hum->arr[number_of_philosophers])
			hum->res->forks[0] = 0;
		else
			hum->res->forks[hum->name] = 0;
		return ;
	}
	if (check_dead_or_ate(hum, tmake(*last_time_eat)) != NULL)
		printf("%d %d has taken a fork\n", tmake(hum->res->time), hum->name);
	if (check_dead_or_ate(hum, tmake(*last_time_eat)) != NULL)
		printf("%d %d is eating\n", tmake(hum->res->time), hum->name);
	gettimeofday(last_time_eat, NULL);
	usleep(hum->arr[time_to_eat] * 1000);
	pthread_mutex_lock(&hum->res->mutex);
	hum->res->forks[hum->name - 1] = 0;
	if (hum->name == hum->arr[number_of_philosophers])
		hum->res->forks[0] = 0;
	else
		hum->res->forks[hum->name] = 0;
	if (check_dead_or_ate(hum, tmake(*last_time_eat)) != NULL)
		printf("%d %d is sleeping\n", tmake(hum->res->time), hum->name);
	usleep(hum->arr[time_to_sleep] * 1000);
	hum->res->forks[hum->name - 1] = 0;
	pthread_mutex_unlock(&hum->res->mutex);
}

t_human	*check_other_side_fork(t_human *hum, struct timeval *last_time_eat)
{
	int	flag;

	flag = 0;
	printf("%d %d is thinking\n", tmake(hum->res->time), hum->name);
	while (flag == 0)
	{
		if (grab_fork(hum, tmake(*last_time_eat), &flag) == 0)
			return (NULL);
	}
	grab_eat_sleep(hum, last_time_eat);
	return (hum);
}

void	*internal_f(void *arg)
{
	t_human			*hum;
	int				flag;
	struct timeval	last_time_eat;

	hum = (t_human *)arg;
	gettimeofday(&last_time_eat, NULL);
	while (1)
	{
		if (check_dead_or_ate(hum, tmake(last_time_eat)) == NULL)
			return (NULL);
		if (grab_fork(hum, tmake(last_time_eat), &flag) == 0)
			return (NULL);
		if (flag == 1)
			grab_eat_sleep(hum, &last_time_eat);
		else
			if (check_other_side_fork(hum, &last_time_eat) == NULL)
				return (NULL);
		/*
		mutex_lock 이것을 포크 함수로 만들어서 0과 1 플래그를 사용해 좌우를 정해줄 수 있다.
		if (right side fork == 0) 이것을 포크 함수로 만들어서 0과 1 플래그를 사용해 좌우를 정해줄 수 있다.
		{
			right side fork = 1
			if (check dead != 0) // print를 체크 데드에 때려박는다면 return (NULL)로 줄을 아낄 수 있다.
				print fork
		}
		mutex_unlock
		if (left side fork = 0)
		{
			left side fork = 1
			if (check dead != 0)
				print eat
			usleep eat
			if (check dead != 0)
				print sleep
			usleep sleep
		}
		else
		{
			print thinking
			while (1)
			{
				check left side fork
				if (left_side fork == 1)
				{
					left side fork = 1
					if (check dead != 0)
						print eat
					if (check dead != 0)
						print sleep
					usleep sleep
					break ;
				}
			}
		}
	//////////////	아 맞다, 사망도 구현해야 함. //////////////
		// 좌측 포크가 비어 있는지 반복체크, 
		// 좌측 포크 쥠
		// 먹은 후 잠
		*/
	}
	/*
	hum = (t_human *)arg;
	gettimeofday(&last_time_eat, NULL);
	printf("%d %d has taken a fork\n", (int)tmake(hum->res->time), hum->name);
	usleep(hum->arr[time_to_eat] * 1000);
	gettimeofday(&last_time_eat, NULL); // 먹고 난 이후 기준인가? 헷갈린다
	if (hum->name == 1)
		printf("%d %d is sleeping\n", (int)tmake(hum->res->time), hum->name);
	if (check_dead_or_ate(hum, hunger_time) == NULL)
		return (NULL);
	else
		printf("%d %d is thinking\n", (int)tmake(hum->res->time), hum->name);
	*/
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
