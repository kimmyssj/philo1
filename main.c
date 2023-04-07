/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:16:44 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/06 21:28:01 by seungjki         ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	int			array[6];
	t_resource	resource; // 공유자원을 놓는 칸
	pthread_t	*thread;

	if (check_args_make_arr(argc, argv, array) == -1)
		return (1);
	if (array[number_of_philosophers] == 1)
		return (0);
	resource.forks = make_fork_and_tomb(array[number_of_philosophers]);
	if (resource.forks == NULL)
		return (1);
	resource.tomb = make_fork_and_tomb(array[number_of_philosophers]);
	if (resource.tomb == NULL)
		return (free_all1(&resource.forks, NULL, NULL));
	resource.dead_flag = 0;
	resource.count = 0;
	resource.flag = 0;
	thread = malloc(sizeof(pthread_t) * array[number_of_philosophers]);
	if (thread == NULL)
		return (free_all1(&resource.forks, &resource.tomb, NULL));
	gettimeofday(&resource.time, NULL);
	if (create_philo(&resource, array, &thread) == 1)
		return (1);
	check_tomb(&resource, array, thread);
	free_all1(&resource.forks, &resource.tomb, &thread);
	return (0);
}
