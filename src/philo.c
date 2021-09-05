/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 12:17:18 by mviudes           #+#    #+#             */
/*   Updated: 2021/09/05 12:32:11 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>

static void	philo_fill_data(t_env *env, int i)
{
	env->philo[i].id = i;
	env->philo[i].env = env;
	env->philo[i].time_to_die = env->time_to_die;
	env->philo[i].time_to_sleep = env->time_to_sleep;
	env->philo[i].time_last_meal = env->time_start;
	env->philo[i].mutex_print = &env->mutex_print;
	env->philo[i].mutex_dead = &env->mutex_dead;
	env->philo[i].is_odd = env->philo[i].id % 2;
	env->philo[i].time_start = env->time_start;
	env->philo[i].check_dead = 0;
	env->philo[i].must_eat_flag = env->must_eat_flag;
}

int	philo_threads_create(t_env *env, int num_of_philo)
{
	int		i;

	env->time_start = time_get_msec(0);
	env->philo = malloc(sizeof(t_philo) * env->num_of_philo);
	if (!env->philo)
		return (0);
	philo_threads_set_forks(env->philo, env->num_of_philo);
	pthread_mutex_init(&env->mutex_print, NULL);
	pthread_mutex_init(&env->mutex_dead, NULL);
	pthread_mutex_unlock(&env->mutex_print);
	pthread_mutex_unlock(&env->mutex_dead);
	i = 0;
	while (i < num_of_philo)
	{
		philo_fill_data(env, i);
		pthread_create(&env->philo[i].thread,
			NULL, philo_rutine, &env->philo[i]);
		i++;
	}
	return (1);
}

void	philo_take_fork(t_philo *philo)
{
	if (!philo->is_odd)
	{
		pthread_mutex_lock(&philo->mutex_left_fork);
		print_messege(philo, "has taken a fork");
		pthread_mutex_lock(philo->mutex_right_fork);
		print_messege(philo, "has taken a fork");
		return ;
	}
	else
	{
		pthread_mutex_lock(philo->mutex_right_fork);
		print_messege(philo, "has taken a fork");
		pthread_mutex_lock(&philo->mutex_left_fork);
		print_messege(philo, "has taken a fork");
		return ;
	}
}
