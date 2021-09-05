/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_rutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 12:21:58 by mviudes           #+#    #+#             */
/*   Updated: 2021/09/05 13:12:54 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>

void	*philo_action_sleep(t_philo *philo)
{
	philo->check_dead = 1;
	print_messege(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
	philo->check_dead = 0;
	return (0);
}

void	*philo_action_eat(t_philo *philo)
{
	philo_take_fork(philo);
	pthread_mutex_lock(philo->mutex_dead);
	print_messege(philo, "is eating");
	philo->time_last_meal = time_get_msec(0);
	pthread_mutex_unlock(philo->mutex_dead);
	ft_usleep(philo->env->time_to_eat);
	pthread_mutex_unlock(&philo->mutex_left_fork);
	pthread_mutex_unlock(philo->mutex_right_fork);
	return (0);
}

void	*philo_action_think(t_philo *philo)
{
	print_messege(philo, "is thinking");
	if (time_get_msec(philo->time_last_meal) + philo->time_to_sleep / 2
		< philo->time_to_die)
		if (philo->env->num_of_philo % 2 != 0 )
			ft_usleep(TIME_ELAPSED);
	return (NULL);
}
