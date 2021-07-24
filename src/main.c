/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:49:57 by mviudes           #+#    #+#             */
/*   Updated: 2021/07/24 20:38:07 by mviudes          ###   ########.fr       */
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

int philo_message(char *message)
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

void *philo_think(void *ptr)
{
	(void)ptr;
	return(ptr);
}

int main(int argc, char *argv[])
{
	t_env *env;
	
	env = get_args(argc, argv);
	(void)env;
	
	printf("This works");
	return(0);
}