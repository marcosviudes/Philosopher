/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 15:54:45 by mviudes           #+#    #+#             */
/*   Updated: 2021/09/04 13:48:11 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>

/*

uint64_t	ft_time(uint64_t start)
{
	uint64_t			current_time;
	struct timeval		aux_clock;

	gettimeofday(&aux_clock, NULL);
	current_time = (uint64_t)
		((aux_clock.tv_usec / 1000) + (aux_clock.tv_sec * 1000));
	return (current_time - start);
}

void	ft_usleep(uint64_t miliseconds)
{
	uint64_t	start;

	start = ft_time(0);
	while (ft_time(start) < miliseconds)
		usleep(1);
}

uint64_t	time_get_msec(void)
{
	uint64_t		ret;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ret = time.tv_sec * 1000;
	ret += time.tv_usec / 1000;
	return(ret);
}*/


uint64_t	time_get_msec(uint64_t start)
{
	uint64_t		ret;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ret = time.tv_sec * 1000;
	ret += time.tv_usec / 1000;
	ret -= start;
	return(ret);
}

void	ft_usleep(uint64_t miliseconds)
{
	uint64_t	start;

	start = time_get_msec(0);
	while (time_get_msec(start) < miliseconds)
		usleep(1);
}