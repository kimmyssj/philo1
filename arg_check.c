/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:29:52 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/14 06:43:21 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_it_number(char *argv)
{
	int	idx;

	idx = 0;
	while (argv[idx])
	{
		if (argv[idx] > '9' || argv[idx] < '0')
			return (-1);
		idx ++;
	}
	return (0);
}

int	check_args_make_arr(int argc, char *argv[], int *array)
{
	int	idx;
	int	temp;

	if (argc < 5 || argc > 6)
		return (-1);
	idx = 0;
	while (argv[1 + idx])
	{
		if (is_it_number(argv[1 + idx]) == -1)
			return (-1);
		temp = ft_atoi(argv[1 + idx]);
		if (temp == -1)
			return (-1);
		array[1 + idx] = temp;
		idx ++;
	}
	if (argc == 5)
		array[5] = -1;
	return (1);
}
