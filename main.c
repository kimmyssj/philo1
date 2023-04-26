/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:16:44 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/26 09:15:37 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_all1(int **arr, int **arr1, pthread_t **thread)
{
	free(*arr);
	free(*arr1);
	free(*thread);
	return (1);
}

void	join_everything(int *array, pthread_t *thread)
{
	int	idx;

	idx = 0;
	while (idx < array[e_nbr_of_philosophers])
	{
		pthread_join(thread[idx], NULL);
		idx ++;
	}
}

void	monitoring_thread(t_resource *resource, int *array, pthread_t *thread)
{
	int	idx;
	int	flag;

	while (array[e_must_eat] != 0)
	{
		idx = 0;
		flag = 0;
		usleep(300);
		pthread_mutex_lock(&resource->mutex);
		while (idx < array[e_nbr_of_philosophers])
		{
			if (resource->tomb[idx] == 1)
				flag ++;
			idx ++;
		}
		if (flag == array[e_nbr_of_philosophers])
			break ;
		pthread_mutex_unlock(&resource->mutex);
	}
	if (array[e_must_eat] != 0)
		pthread_mutex_unlock(&resource->mutex);
	join_everything(array, thread);
}

void	initialize(t_resource *resource)
{
	resource->dead_flag = 0;
	resource->count = 0;
	resource->flag = 0;
}

int	main(int argc, char *argv[])
{
	int			array[6];
	t_resource	resource;
	pthread_t	*thread;
	t_human		*hum;

	if (check_args_make_arr(argc, argv, array) == -1)
		return (1);
	resource.forks = make_fork_and_tomb(array[e_nbr_of_philosophers]);
	if (resource.forks == NULL)
		return (1);
	resource.tomb = make_fork_and_tomb(array[e_nbr_of_philosophers]);
	if (resource.tomb == NULL)
		return (free_all1(&resource.forks, NULL, NULL));
	initialize(&resource);
	thread = malloc(sizeof(pthread_t) * array[e_nbr_of_philosophers]);
	if (thread == NULL)
		return (free_all1(&resource.forks, &resource.tomb, NULL));
	hum = create_philo(&resource, array, &thread);
	if (hum == NULL)
		return (free_all1(NULL, NULL, &thread));
	monitoring_thread(&resource, array, thread);
	free_all1(&resource.forks, &resource.tomb, &thread);
	destroy_all_mutex(&resource, array);
	free(hum);
	return (0);
}
