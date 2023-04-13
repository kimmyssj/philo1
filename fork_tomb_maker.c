/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_tomb_maker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 06:59:15 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/14 06:59:17 by seungjki         ###   ########.fr       */
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
