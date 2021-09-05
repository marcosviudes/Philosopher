/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messege.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 12:23:00 by mviudes           #+#    #+#             */
/*   Updated: 2021/09/05 12:23:10 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>

void	print_messege(t_philo *philo, char *messege)
{
	uint64_t	actual_time;

	pthread_mutex_lock(philo->mutex_print);
	actual_time = time_get_msec(0);
	actual_time -= philo->time_start;
	printf("[%6llu ms]:\t (%i)  %s\n", actual_time, philo->id + 1, messege);
	pthread_mutex_unlock(philo->mutex_print);
}
