/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:49:57 by mviudes           #+#    #+#             */
/*   Updated: 2021/09/05 12:31:52 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>

void	*philo_check_dead(t_env *env)
{
	int			i;

	i = 0;
	while (42)
	{
		if (i == env->num_of_philo)
			i = 0;
		if (time_get_msec(env->philo[i].time_last_meal)
			> (uint64_t)env->time_to_die)
			return (kill_me(env, i));
		if (env->must_eat_flag)
		{
			if (!env->philo[i].must_eat_end
				&& env->philo[i].must_eat_num == env->n_must_eat)
			{
				env->philo[i].must_eat_end = 0;
				env->must_eat_all_finish++;
			}
			if (env->must_eat_all_finish == (env->num_of_philo))
				return (dead_clean_exit(env));
		}
		i++;
	}
	return (0);
}

void	philo_threads_set_forks(t_philo *philo, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_init(&philo[i].mutex_left_fork, NULL);
		pthread_mutex_unlock(&philo[i].mutex_left_fork);
		if (i != 0)
			philo[i - 1].mutex_right_fork = &philo[i].mutex_left_fork;
		i++;
	}
	philo[num_of_philos - 1].mutex_right_fork = &philo[0].mutex_left_fork;
}

void	philo_threads_destroy(t_env *env, int num_of_philo)
{
	int		i;

	pthread_mutex_destroy(&env->mutex_print);
	pthread_mutex_destroy(&env->mutex_dead);
	i = 0;
	while (i < num_of_philo)
	{
		pthread_mutex_destroy(&env->philo[i].mutex_left_fork);
		pthread_detach(env->philo[i].thread);
		i++;
	}
}

void	*philo_rutine(void *arg)
{
	t_philo	*philo;

	philo = ((t_philo *)arg);
	philo->first_time = 1;
	if (philo->env->num_of_philo % 2 == 0)
		if (!(philo->id % 2))
			ft_usleep(TIME_ELAPSED);
	while (1)
	{
		philo_action_eat(philo);
		philo_action_sleep(philo);
		philo_action_think(philo);
		if (philo->must_eat_flag)
			philo->must_eat_num++;
	}
	pthread_mutex_unlock(&philo->mutex_left_fork);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_env	*env;

	env = NULL;
	env = args_getter(argc, argv);
	if (!env)
		return (exit_error(env));
	if (!philo_threads_create(env, env->num_of_philo))
		return (exit_error(env));
	philo_check_dead(env);
	philo_threads_destroy(env, env->num_of_philo);
	clear_all(env);
	return (0);
}
