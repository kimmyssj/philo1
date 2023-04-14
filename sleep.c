/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjki <seungjki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:11:34 by seungjki          #+#    #+#             */
/*   Updated: 2023/04/15 01:54:15 by seungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_human	*ssleep(t_human *hum, struct timeval *last_time)
{
	if (check_dead_or_ate(hum, last_time, sleeping) == NULL)
		return (NULL);
	usleep_split(hum, *last_time, time_to_sleep, 0);
	return (hum);
}
