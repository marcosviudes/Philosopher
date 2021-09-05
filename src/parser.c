/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 15:56:38 by mviudes           #+#    #+#             */
/*   Updated: 2021/09/05 19:46:23 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>

int	args_checker(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	while (argc-- > 1)
		if (!ft_isnum(argv[argc]))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_env	*args_getter(int argc, char **argv)
{
	t_env	*ret;

	ret = NULL;
	if (args_checker(argc, argv))
		return (NULL);
	ret = malloc(sizeof(t_env));
	if (!ret)
		return (NULL);
	ret->num_of_philo = ft_absatol(argv[1]);
	ret->time_to_die = ft_absatol(argv[2]);
	ret->time_to_eat = ft_absatol(argv[3]);
	ret->time_to_sleep = ft_absatol(argv[4]);
	ret->must_eat_flag = 0;
	if (argc == 6)
	{
		ret->n_must_eat = ft_absatol(argv[5]);
		ret->must_eat_flag = 1;
	}
	if (ret->num_of_philo > MAX_PHILOS || ret->num_of_philo < 1
		|| ret->time_to_die < 1
		|| ret->time_to_eat < 1
		|| ret->time_to_sleep < 1
		|| ret->n_must_eat < 0)
		return (NULL);
	return (ret);
}
