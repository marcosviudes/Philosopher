/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 12:18:23 by mviudes           #+#    #+#             */
/*   Updated: 2021/09/05 12:31:33 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>

int	exit_error(t_env *env)
{
	clear_all(env);
	ft_putendl_fd("Error", STDERR_FILENO);
	return (-1);
}

void	clear_all(t_env *env)
{
	if (env)
		if (env->philo)
			free(env->philo);
	if (env)
		free(env);
}

void	*kill_me(t_env *env, int i)
{
	uint64_t	actual_time;

	pthread_mutex_lock(env->philo[i].mutex_print);
	pthread_mutex_lock(env->philo[i].mutex_dead);
	actual_time = time_get_msec(0);
	actual_time -= env->time_start;
	printf("[%6llu ms]:\t (%i)  died", actual_time, i);
	return (NULL);
}

void	*dead_clean_exit(t_env *env)
{
	pthread_mutex_lock(env->philo->mutex_print);
	pthread_mutex_lock(env->philo->mutex_dead);
	return (0);
}
