/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:49:57 by mviudes           #+#    #+#             */
/*   Updated: 2021/08/23 21:13:10 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>

/* -> 3 310 150 150. (Death at 310)
 * -> 3 310 100 100. (Periodic)
 * -> 3 310 105 104. (Periodic)
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
	{
		usleep(1);
	}
}

void	print_messege(uint64_t actual_time, t_philo *philo, char *messege)
{

	pthread_mutex_lock(philo->mutex_print);
	actual_time = time_get_msec();
	actual_time -= philo->time_start;
	printf("[%6llu ms]:\t (%i)  %s\n", actual_time, philo->id + 1, messege);
	pthread_mutex_unlock(philo->mutex_print);
}

uint64_t	time_get_msec(void)
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

void *philo_action_sleep(t_philo *philo)
{
	uint64_t actual_time;

	actual_time = time_get_msec();
	actual_time -= philo->env->start_time;
	print_messege(actual_time, philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
	return(0);
}

void philo_take_fork(t_philo *philo)
{
	uint64_t actual_time;

	actual_time = time_get_msec();
	actual_time -= philo->time_start;

	if(philo->is_odd)
	{
		pthread_mutex_lock(&philo->mutex_left_fork);
		print_messege(actual_time, philo, "has taken right fork");
		pthread_mutex_lock(philo->mutex_right_fork);
		print_messege(actual_time, philo, "has taken left  fork");
		print_messege(actual_time, philo, "is eating");
	}
	else
	{
		pthread_mutex_lock(philo->mutex_right_fork);
		print_messege(actual_time, philo, "has taken left  fork");
		pthread_mutex_lock(&philo->mutex_left_fork);
		print_messege(actual_time, philo, "has taken right fork");
		print_messege(actual_time, philo, "is eating");
	}
}
void *philo_action_eat(t_philo *philo)
{
	uint64_t actual_time;

	actual_time = time_get_msec();
	actual_time -= philo->time_start;//philo->env->start_time;

	philo_take_fork(philo);
	philo->time_last_meal = time_get_msec() - actual_time;
	ft_usleep(philo->env->time_to_eat);
	pthread_mutex_unlock(&philo->mutex_left_fork);
	pthread_mutex_unlock(philo->mutex_right_fork);
	return(0);
}

void *philo_action_think(t_philo *philo)
{
	uint64_t actual_time;

	actual_time = time_get_msec();
	actual_time -= philo->time_start;
	print_messege(actual_time, philo, "is thinking");
	return(NULL);
}

void	*philo_check_dead(t_philo *philo)
{
	uint64_t actual_time;

	actual_time = time_get_msec();
	actual_time -= philo->time_last_meal;
	
	if (actual_time >= philo->time_to_die)
	//	exit(0);
	return(NULL);
	return(NULL);
}

void *philo_rutine(void *arg)
{
	t_philo	*philo;

	philo = ((t_philo*)arg);
	while(1)
	{
		philo_check_dead(philo);
		philo_action_eat(philo);
		philo_action_sleep(philo);
		philo_action_think(philo);
	}
}
void	philo_threads_set_forks(t_philo *philo, int num_of_philos)
{
	int temp;
	
	temp = num_of_philos;
	while(temp--)
	{
		pthread_mutex_init(&philo[temp].mutex_left_fork, NULL);
		pthread_mutex_unlock(&philo[temp].mutex_left_fork);
		philo[temp - 1].mutex_right_fork = &philo[temp].mutex_left_fork;
	}
	philo[num_of_philos - 1].mutex_right_fork = &philo[0].mutex_left_fork;
}

void	philo_threads_create(t_env *env, int num_of_philo)
{
	int		i;
	uint64_t time_start;

	time_start = time_get_msec();
	env->philo = malloc(sizeof(t_philo) * env->num_of_philo);
	if(!env->philo)
		exit_error("Imposible to malloc a philo :(");
	philo_threads_set_forks(env->philo, env->num_of_philo);
	pthread_mutex_init(&env->mutex_print, NULL);
	pthread_mutex_unlock(&env->mutex_print);
	i =  0;
	while(i < num_of_philo)
	{
		env->philo[i].id = i;
		env->philo[i].env = env;
		env->philo[i].time_to_die = env->time_to_die;
		env->philo[i].time_to_sleep = env->time_to_sleep;
		env->philo[i].time_last_meal = time_get_msec();
		env->philo[i].mutex_print = &env->mutex_print;
		env->philo[i].is_odd = env->philo[i].id % 2;
		env->philo[i].time_start = time_start;
		pthread_create(&env->philo[i].thread, NULL, philo_rutine, &env->philo[i]);
		i++;
	}
	
}

void	philo_threads_start(t_env *env, int num_of_philo)
{
	while(--num_of_philo)
		pthread_join(env->philo[num_of_philo].thread, NULL);
}

int main(int argc, char *argv[])
{
	t_env *env;

	env = args_getter(argc, argv);
	env->start_time = time_get_msec();
	philo_threads_create(env, env->num_of_philo);
	philo_threads_start(env, env->num_of_philo);
	return(0);
}