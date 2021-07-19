/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 21:36:34 by mviudes           #+#    #+#             */
/*   Updated: 2021/07/19 22:08:37 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int			id;
}				t_philo;

typedef struct s_env
{
	int			num_of_philo;
	int			t_to_die;
	int			t_to_eat;
	int			t_to_sleep;
	int			n_must_eat;
	t_philo		*philo;
}				t_env;

void	exit_error(char *string);
int		ft_isnum(char *string);
size_t	ft_strlen(const char *str);
#endif
