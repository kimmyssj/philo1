/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:23:23 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/26 08:00:11 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PIPEX_H

# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

enum
{
	eating,
	sleeping,
	thinking,
	grabfork,
	no_print
};

enum
{
	fail,
	success
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

enum
{
	max,
	novice
};

typedef struct s_resource
{
	struct timeval		time;
	int					dead_flag;
	int					count;
	int					flag;
	int					*forks;
	int					*tomb;
	pthread_mutex_t		mutex;
	pthread_mutex_t		*mfork;
}	t_resource;

typedef struct s_human
{
	t_resource		*res;
	int				*arr;
	int				flag;
	int				ate_numb;
	int				name;
	struct timeval	time;
}	t_human;

int				check_args_make_arr(int argc, char *argv[], int *array);
int				error_message(int flag);
int				ft_atoi(char *str);
int				free_all1(int **arr, int **arr1, pthread_t **thread);
int				timestamp(t_human *hum, struct timeval time);
int				ssleep(t_human *hum, struct timeval *last_time);
int				eat(t_human *hum, struct timeval *last_time, int flag);
int				check_novice_hand(t_human *hum);
int				check_both_hands(t_human *hum, int flag);
int				grab_fork_max(t_human *hum, struct timeval *last_time);
int				grab_fork_novice(t_human *hum, struct timeval *last_time);
int				*make_fork_and_tomb(int num);
void			usleep_split1(int time);
void			usleep_split(t_human *h, struct timeval t, int f, int f1);
void			print_in_mutex(t_human *hum, int flag);
void			destroy_all_mutex(t_resource *res, int *arr);
void			*internal_f(void *arg);
t_human			*create_philo(t_resource *res, int *arr, pthread_t **thread);
t_human			*dead(t_human *hum, struct timeval *last_time);
t_human			*check_dead_or_ate(t_human *h, struct timeval *l, int g);
t_human			*if_failed(t_resource **res, t_human **hum);
pthread_mutex_t	*fork_mutex_maker(int hum_num);

#endif
