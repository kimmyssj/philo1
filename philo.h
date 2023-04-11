/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:23:23 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/11 04:56:27 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PIPEX_H

#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>

enum{
	not_valid_args,
	malloc_failed
};

enum
{
	philo = 0,
	number_of_philosophers = 1,
	time_to_die = 2,
	time_to_eat = 3,
	time_to_sleep = 4,
	must_eat = 5
};

typedef struct s_resource // 공통자원을 위한 공간으로 만들자
{
	struct timeval		time;
	int					dead_flag;
	int					count;
	int					flag;
	int					*forks;
	int					*tomb;
	pthread_mutex_t		mutex;
	pthread_mutex_t		mutex1;
	pthread_mutex_t		mutex2;
}	t_resource;

typedef struct	s_human
{
	t_resource	*res;
	int			*arr;
	int			ate_numb;
	int			name;
}	t_human;

int		check_args_make_arr(int argc, char *argv[], int *array);
int		create_philo(t_resource *res, int *arr, pthread_t **thread);
int		error_message(int flag);
int		ft_atoi(char *str);
int		free_all1(int **arr, int **arr1, pthread_t **thread);
int		*make_fork_and_tomb(int num);

#endif
