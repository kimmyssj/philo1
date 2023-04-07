/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 02:03:24 by seungjki          #+#    #+#             */
/*   Updated: 2023/02/10 18:35:48 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	result_maker(const char *str)
{
	long long	result;
	long long	flag;
	int			idx1;

	result = 0;
	flag = 0;
	idx1 = 0;
	if (str[idx1] == '-')
	{
		idx1 ++;
		flag = 1;
	}
	while (str[idx1] && str[idx1] >= '0' && str[idx1] <= '9')
	{
		result = result * 10;
		result = result + str[idx1] - '0';
		idx1++;
	}
	if (flag == 1)
		result = result * -1;
	return (result);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	idx;

	idx = 0;
	if (n == 0)
		return (0);
	while (s1[idx] && s1[idx] == s2[idx] && idx < n)
		idx ++;
	if (idx == n)
		return (0);
	return ((unsigned char)s1[idx] - (unsigned char)s2[idx]);
}

int	check_under_over(char *str)
{
	int	idx;

	idx = 0;
	if (str[idx] == '-')
	{
		idx ++;
		while (str[idx] >= '0' && str[idx] <= '9')
			idx ++;
		if (idx == 11)
			if (ft_strncmp("-2147483648", str, 11) > 0)
				return (-1);
		if (idx > 11)
			return (-1);
	}
	else
	{
		while (str[idx] >= '0' && str[idx] <= '9')
			idx ++;
		if (idx == 10)
			if (ft_strncmp("2147483647", str, 10) > 0)
				return (-1);
		if (idx > 10)
			return (-1);
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	result;

	if (check_under_over(str) == -1)
		return (-1);
	result = result_maker(str);
	return (result);
}
