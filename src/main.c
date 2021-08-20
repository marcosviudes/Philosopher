/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:49:57 by mviudes           #+#    #+#             */
/*   Updated: 2021/08/18 13:29:16 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>


uint64_t	time_get(void)
{
	uint64_t		ret;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ret = time.tv_sec * 1000;
	ret += time.tv_usec / 1000;
	return(ret);
}

void	args_checker(int argc, char **argv)
{
	if(argc < 5 || argc > 6)
		exit_error("invalid num of args\n");
	while(argc-- > 1)
		if(!ft_isnum(argv[argc]))
			exit_error("argumenst should be numbers\n");
}

t_env	*args_getter(int argc, char **argv)
{
	t_env *ret;

	args_checker(argc, argv);
	ret = malloc(sizeof(t_env));
	if(!ret)
		exit_error("imposible to malloc\n");
	ret->num_of_philo = ft_absatol(argv[1]);
	ret->time_to_die = ft_absatol(argv[2]);
	ret->time_to_eat = ft_absatol(argv[3]);
	ret->time_to_sleep = ft_absatol(argv[4]);
	ret->n_must_eat = 0;
	if(argc == 6)
		ret->n_must_eat = ft_absatol(argv[5]);

	printf("\targ 1: |%ld|\n\targ 2: |%ld|\n\targ 3: |%ld|\n\targ 4: |%ld|\n\targ 5: |%ld|\n",
			ret->num_of_philo, ret->time_to_die, ret->time_to_eat, ret->time_to_sleep, ret->n_must_eat);
	return(ret);
}

void	exit_error(char *string)
{
	write(2, string, ft_strlen(string));
	exit(-1);
}

int	exit_clear_all(t_env *env)
{
	if(env)
		free(env);
	exit(0);
}

void *philo_action_sleep(void *ptr)
{
	(void)ptr;
	return(ptr);
}

void *philo_action_eat(void *ptr)
{
	(void)ptr;
	return(ptr);
}

void *philo_action_think(t_philo *philo)
{
	uint64_t actual_time;

	actual_time = time_get();
	actual_time -= philo->env->start_time;
	printf("[%-4llu ms]:\tphilo %i is thinking\n", actual_time, philo->id);
	return(NULL);
}

void *philo_rutine(void *arg)
{
	t_philo	*philo;

	philo = ((t_philo*)arg);
	void *ptr = NULL;;
	while(1)
	{
		philo_action_eat(philo);
		philo_action_sleep(philo);
		philo_action_think(philo);
		usleep(3000);
	}
}
void	philo_threads_set_forks(t_philo *philo, int num_of_philos)
{
	/*philo[num_of_philos - 1].right_fork = &philo[0].fork;
	while(num_of_philos--)
		philo[num_of_philos - 1].right_fork = &philo[num_of_philos].fork;*/
	philo[num_of_philos - 1].right_fork = pthread_mutex_init(&philo[0].fork);
	while(num_of_philos--)
		philo[num_of_philos - 1].right_fork = &philo[num_of_philos].fork;
}

void	philo_threads_create(t_env *env)
{
	int		i;

	i =  0;
	env->philo = malloc(sizeof(t_philo) * env->num_of_philo);
	if(!env->philo)
		exit_error("Imposible to malloc a philo :(");
	philo_threads_set_forks(env->philo, env->num_of_philo);
	while(i < env->num_of_philo)
	{
		env->philo[i].id = i;
		env->philo[i].env = env;
		env->philo[i].time_to_die = env->time_to_die;
		pthread_create(&env->philo[i].thread, NULL, philo_rutine, &env->philo[i]);
		i++;
	}
	
}

void	philo_threads_start(t_env *env)
{
	int	i;

	i = 0;
	while(i < env->num_of_philo)
	{
		pthread_join(env->philo[i].thread, NULL);
		i++;
	}
}

int main(int argc, char *argv[])
{
	t_env *env;
	
	env = args_getter(argc, argv);
	env->start_time = time_get();
	philo_threads_create(env);
	philo_threads_start(env);
	return(0);
}