/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_tomb_making.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:44:36 by seungjki          #+#    #+#             */
/*   Updated: 2023/03/22 22:18:51 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*make_fork_and_tomb(int num)
{
	int	*answer;
	int	idx;

	idx = 0;
	answer = malloc(sizeof(int) * num);
	if (answer == NULL)
		return (NULL);
	while (idx < num)
	{
		answer[idx] = 0;
		idx ++;
	}
	return (answer);
}
