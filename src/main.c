/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:49:57 by mviudes           #+#    #+#             */
/*   Updated: 2021/08/09 18:23:30 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>

void	check_args(int argc, char **argv)
{
	if(argc < 5 || argc > 6)
		exit_error("invalid num of args\n");
	while(argc-- > 1)
		if(!ft_isnum(argv[argc]))
			exit_error("argumenst should be numbers\n");
}

t_env	*get_args(int argc, char **argv)
{
	t_env *ret;

	check_args(argc, argv);
	ret = malloc(sizeof(t_env));
	if(!ret)
		exit_error("imposible to malloc\n");
	ret->num_of_philo = ft_absatol(argv[1]);
	ret->t_to_die = ft_absatol(argv[2]);
	ret->t_to_eat = ft_absatol(argv[3]);
	ret->t_to_sleep = ft_absatol(argv[4]);
	ret->n_must_eat = 0;
	if(argc == 6)
		ret->n_must_eat = ft_absatol(argv[5]);

	printf("\targ 1: |%ld|\n\targ 2: |%ld|\n\targ 3: |%ld|\n\targ 4: |%ld|\n\targ 5: |%ld|\n",
			ret->num_of_philo, ret->t_to_die, ret->t_to_eat, ret->t_to_sleep, ret->n_must_eat);
	return(ret);
}

void	exit_error(char *string)
{
	write(2, string, ft_strlen(string));
	exit(-1);
}

int	clear_all(t_env *env)
{
	if(env)
		free(env);
	exit(0);
}
int checkargs()
{
	return(1);
}

int philo_message(int id, char *message)
{
	(void)message;
	return (0);
}
void *philo_sleep(void *ptr)
{
	(void)ptr;
	return(ptr);
}

void *philo_eat(void *ptr)
{
	(void)ptr;
	return(ptr);
}

void *philo_think(t_philo *philo)
{
	//philo_message(, "is thinking");
//	write(1, "philo ", 6);
//	ft_putnbr_fd(1, philo->id);
//	write(1, "is thinking\n", 12);
	//write(1, "\n", 1);
	printf("[%-3i]:\tphilo %i is thinking\n",env->time, philo->id);
	return(NULL);
}

void *philo_rutine(void *arg)
{
	t_philo	*philo;

	philo = ((t_philo*)arg);
	void *ptr = NULL;;
	while(1)
	{
		philo_eat(ptr);
		philo_sleep(ptr);
		philo_think(philo);
		sleep(1);
	}
}

void philo_create(t_env *env)
{
	int		i;

	i =  0;
	env->philo = malloc(sizeof(t_philo) * env->num_of_philo);
	while(i < env->num_of_philo)
		{
			env->philo[i].id = i;
			pthread_create(&env->philo[i].thread, NULL, philo_rutine, &env->philo[i]);
			i++;
		}
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
	
	env = get_args(argc, argv);

	philo_create(env);
	//philo_rutine();
	printf("This works");
	return(0);
}