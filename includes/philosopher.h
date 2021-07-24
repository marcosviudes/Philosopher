/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 21:36:34 by mviudes           #+#    #+#             */
/*   Updated: 2021/07/24 20:36:24 by mviudes          ###   ########.fr       */
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
# include <limits.h>

#define NUM_OF_ARGS

typedef struct s_philo
{
	int			id;
}				t_philo;

typedef struct s_env
{
	long			num_of_philo;
	long			t_to_die;
	long			t_to_eat;
	long			t_to_sleep;
	long			n_must_eat;
	t_philo		*philo;
}				t_env;

void	exit_error(char *string);
int		ft_isnum(char *string);
size_t	ft_strlen(const char *str);
long	ft_absatol(const char *string);
void	ft_putendl_fd(char *s, int fd);

#endif
