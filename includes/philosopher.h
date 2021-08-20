/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 21:36:34 by mviudes           #+#    #+#             */
/*   Updated: 2021/08/18 13:28:53 by mviudes          ###   ########.fr       */
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
# include <stdint.h>

#define NUM_OF_ARGS

struct s_env;

typedef struct s_philo
{
	int						id;
	uint64_t				time_to_die;
	int						fork;
	int						have_eated;
	pthread_t				thread;
	pthread_mutex_t			mutex_fork;
	pthread_mutex_t			*right_fork;
	struct s_env	*env;
	
}				t_philo;

typedef struct s_env
{
	long			num_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			n_must_eat;
//	time_t			time;
	uint64_t		start_time;
	t_philo			*philo;
}				t_env;

void	exit_error(char *string);
int		ft_isnum(char *string);
size_t	ft_strlen(const char *str);
long	ft_absatol(const char *string);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);

uint64_t	time_get(void);

void	args_checker(int argc, char **argv);
t_env	*args_getter(int argc, char **argv);

void	exit_error(char *string);
int		exit_clear_all(t_env *env);

void	philo_threads_create(t_env *env);
void	philo_threads_start(t_env *arg);
void	philo_threads_set_forks(t_philo *philo, int num_of_philos);
void	*philo_action_sleep(t_philo *philo);
void	*philo_action_eat(t_philo *philo);
void	*philo_action_eat(t_philo *philo);

#endif

