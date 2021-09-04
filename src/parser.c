/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 15:56:38 by mviudes           #+#    #+#             */
/*   Updated: 2021/09/04 16:50:47 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>

void	args_checker(int argc, char **argv)
{
	if(argc < 5 || argc > 6)
		exit_error("Invalid num of args\n");
	while(argc-- > 1)
		if(!ft_isnum(argv[argc]))
			exit_error("Argumenst should be numbers\n");
}

t_env	*args_getter(int argc, char **argv)
{
	t_env *ret;

	ret = NULL;
	args_checker(argc, argv);
	ret = malloc(sizeof(t_env));
	if(!ret)
		exit_error("imposible to malloc\n");
	ret->num_of_philo = ft_absatol(argv[1]);
	ret->time_to_die = ft_absatol(argv[2]);
	ret->time_to_eat = ft_absatol(argv[3]);
	ret->time_to_sleep = ft_absatol(argv[4]);
	ret->must_eat_flag = 0;
	if(argc == 6)
	{
		ret->n_must_eat = ft_absatol(argv[5]);
		ret->must_eat_flag = 1;
	}
	if(ret->num_of_philo > 200 || ret->time_to_die < 1 || ret->time_to_eat < 1 || ret->time_to_sleep < 1 || ret->n_must_eat < 0)
		return(NULL);
	printf("\targ 1: |%ld|\n\targ 2: |%ld|\n\targ 3: |%ld|\n\targ 4: |%ld|\n\targ 5: |%ld|\n",
			ret->num_of_philo, ret->time_to_die, ret->time_to_eat, ret->time_to_sleep, ret->n_must_eat);
	return(ret);
}
/*
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
}*/