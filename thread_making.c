/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_making.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:11:34 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/26 09:16:29 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	give_philos_life(t_human *hum, int *arr, t_resource *res)
{
	int	idx;

	idx = 0;
	while (idx < arr[e_nbr_of_philosophers])
	{
		hum[idx].res = res;
		hum[idx].arr = arr;
		hum[idx].name = idx + 1;
		hum[idx].ate_numb = 0;
		hum[idx].flag = 0;
		idx ++;
	}
}

t_human	*create_philo(t_resource *res, int *arr, pthread_t **thread)
{
	t_human	*hum;
	int		idx;

	hum = malloc(sizeof(t_human) * arr[e_nbr_of_philosophers]);
	if (hum == NULL)
	{
		free_all1(&res->forks, &res->tomb, NULL);
		free(res);
		return (NULL);
	}
	pthread_mutex_init(&res->mutex, NULL);
	res->mfork = fork_mutex_maker(arr[e_nbr_of_philosophers]);
	if (res->mfork == NULL)
		return (if_failed(&res, &hum));
	gettimeofday(&res->time, NULL);
	give_philos_life(hum, arr, res);
	if (arr[e_must_eat] == 0)
		return (hum);
	idx = 0;
	while (idx < arr[e_nbr_of_philosophers])
	{
		pthread_create(*thread + idx, NULL, internal_f, hum + idx);
		idx ++;
	}
	return (hum);
}
