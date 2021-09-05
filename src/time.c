/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 15:54:45 by mviudes           #+#    #+#             */
/*   Updated: 2021/09/04 20:32:56 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>

uint64_t	time_get_msec(uint64_t start)
{
	uint64_t		ret;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ret = time.tv_sec * 1000;
	ret += time.tv_usec / 1000;
	ret -= start;
	return (ret);
}

void	ft_usleep(uint64_t miliseconds)
{
	uint64_t	start;

	start = time_get_msec(0);
	while (time_get_msec(start) < miliseconds)
		usleep(1);
}
