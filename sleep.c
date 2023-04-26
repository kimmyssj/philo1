/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:11:34 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/26 09:19:16 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ssleep(t_human *hum, struct timeval *last_time)
{
	if (check_dead_or_ate(hum, last_time, e_sleeping) == NULL)
		return (e_fail);
	usleep_split(hum, *last_time, e_time_to_sleep, 0);
	return (e_success);
}
