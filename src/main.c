/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:49:57 by mviudes           #+#    #+#             */
/*   Updated: 2021/09/04 17:51:14 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>

/* -> 3 310 150 150. (Death at 310)
 * -> 3 310 100 100. (Periodic) // 310/2 == 155
 * -> 3 310 105 104. (Periodic) // should die?
 * -> 3 299 100 100. (Death at 299)
 * -> 2 310 150 150. (Periodic)
 *  ->3 310 103 103. (Periodic)
 */

/*
void	ft_usleep(uint64_t miliseconds)
{
	uint64_t	end;

	end = time_get_msec();
	end += miliseconds;

	while (end > time_get_msec())
		usleep(1);
}
*/



void	print_messege(t_philo *philo, char *messege)
{
	uint64_t actual_time;
	
	pthread_mutex_lock(philo->mutex_print);
	actual_time = time_get_msec(0);
	actual_time -= philo->time_start;
	printf("[%6llu ms]:\t (%i)  %s\n", actual_time, philo->id, messege);
	pthread_mutex_unlock(philo->mutex_print);
}

void	exit_error(char *string)
{
	write(2, string, ft_strlen(string));
	exit(-1);
}

void	clear_all(t_env *env)
{
	if(env->philo)
		free(env->philo);
	if(env)
		free(env);
}

void *philo_action_sleep(t_philo *philo)
{
	philo->check_dead = 1;
	print_messege(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
	philo->check_dead = 0;
	return(0);
}

void philo_take_fork(t_philo *philo)
{
	if(!philo->is_odd)
	{
		pthread_mutex_lock(&philo->mutex_left_fork);
		print_messege(philo, "has taken left  fork");
		pthread_mutex_lock(philo->mutex_right_fork);
		print_messege(philo, "has taken right fork");
		return;
	}
	else
	{
		pthread_mutex_lock(philo->mutex_right_fork);
		print_messege(philo, "has taken right fork");
		pthread_mutex_lock(&philo->mutex_left_fork);
		print_messege(philo, "has taken left  fork");
		return;
	}
}
void *philo_action_eat(t_philo *philo)
{
	//philo->check_dead = 1;
	philo_take_fork(philo);
	pthread_mutex_lock(philo->mutex_dead);
	print_messege(philo, "is eating");
	philo->time_last_meal = time_get_msec(0);
	pthread_mutex_unlock(philo->mutex_dead);
	ft_usleep(philo->env->time_to_eat);
//	philo->check_dead = 0;
	pthread_mutex_unlock(&philo->mutex_left_fork);
	pthread_mutex_unlock(philo->mutex_right_fork);
	return(0);
}

void *philo_action_think(t_philo *philo)
{
	print_messege(philo, "is thinking");
	if(time_get_msec(philo->time_last_meal) + philo->time_to_sleep/2 < philo->time_to_die){
		if(philo->env->num_of_philo % 2 != 0 )
		{
			ft_usleep(TIME_ELAPSED);
			print_messege(philo, "is waiting");
		}
	}
	philo->first_time = 0;
	return(NULL);
}

void	*philo_check_dead(t_env *env)
{
	int		i;
	i = 0;
	while(42)
	{
		if(i == env->num_of_philo)
			i = 0;
		if(time_get_msec(env->philo[i].time_last_meal) > (uint64_t)env->time_to_die )
		{
			fprintf(stderr, "%llu\n", time_get_msec(env->philo[i].time_last_meal));
			pthread_mutex_lock(env->philo[i].mutex_dead);
			print_messege(&env->philo[i], "is dead");
			return(0);
		}
		if(env->must_eat_flag)
		{
			if(!env->philo[i].must_eat_end && env->philo[i].must_eat_num == env->n_must_eat)
			{
				env->philo[i].must_eat_end = 0;
				env->must_eat_all_finish++;
			}
			if(env->must_eat_all_finish == (env->num_of_philo))
				return(0);
		}
		i++;
	}
	return(0);
}

void *philo_rutine(void *arg)
{
	t_philo	*philo;

	philo = ((t_philo*)arg);
	philo->first_time = 1;
	while(1)//&& philo->n_must_eat)
	{
		philo_action_eat(philo);
		philo_action_sleep(philo);
		philo_action_think(philo);
		if(philo->must_eat_flag)
			philo->must_eat_num++;
	}
	pthread_mutex_unlock(&philo->mutex_left_fork);
	return(NULL);
}
void	philo_threads_set_forks(t_philo *philo, int num_of_philos)
{
	int i;
	
	i = 0;
	while(i < num_of_philos)
	{
		pthread_mutex_init(&philo[i].mutex_left_fork, NULL);
		pthread_mutex_unlock(&philo[i].mutex_left_fork);
		if(i != 0)
			philo[i - 1].mutex_right_fork = &philo[i].mutex_left_fork;
		i++;
	}
	philo[num_of_philos - 1].mutex_right_fork = &philo[0].mutex_left_fork;
}

void philo_fill_data(t_env *env, int i)
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
		//env->philo[i].n_must_eat;
}
void	philo_threads_create(t_env *env, int num_of_philo)
{
	int		i;

	env->time_start = time_get_msec(0);
	env->philo = malloc(sizeof(t_philo) * env->num_of_philo);
	if(!env->philo)
		exit_error("Imposible to malloc a philo :(");
	philo_threads_set_forks(env->philo, env->num_of_philo);
	pthread_mutex_init(&env->mutex_print, NULL);
	pthread_mutex_init(&env->mutex_dead, NULL);
	pthread_mutex_unlock(&env->mutex_print);
	pthread_mutex_unlock(&env->mutex_dead);
	i =  0;
	while(i < num_of_philo)
	{
		philo_fill_data(env, i);
		pthread_create(&env->philo[i].thread, NULL, philo_rutine, &env->philo[i]);
		i++;
	}
	env->start = 1;
}

void	philo_threads_destroy(t_env *env, int num_of_philo)
{
	int		i;
	
	i = 0;

	pthread_mutex_destroy(&env->mutex_print);
	pthread_mutex_destroy(&env->mutex_dead);
	while(i < num_of_philo)
	{
		pthread_mutex_destroy(&env->philo[i].mutex_left_fork);
		pthread_detach(env->philo[i].thread);
		//pthread_join(env->philo[i].thread, NULL);
		i++;
	}
}

int main(int argc, char *argv[])
{
	t_env *env;

	env = NULL;
	env = args_getter(argc, argv);
	philo_threads_create(env, env->num_of_philo);
//	while(1){}
	philo_check_dead(env);
	philo_threads_destroy(env, env->num_of_philo);
	clear_all(env);
//	system("leaks philo");
	return(0);
}