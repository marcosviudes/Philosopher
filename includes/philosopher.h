/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 21:36:34 by mviudes           #+#    #+#             */
/*   Updated: 2021/09/05 12:30:23 by mviudes          ###   ########.fr       */
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
# include <stdbool.h>

# define NUM_OF_ARGS
# define MAX_PHILOS 200
# define TIME_ELAPSED 10

struct	s_env;

typedef struct s_philo
{
	int				id;
	int				is_odd;
	int				first_time;
	int				check_dead;
	int				must_eat_num;
	bool			must_eat_flag;
	bool			must_eat_end;		
	uint64_t		time_start;
	uint64_t		time_to_die;
	uint64_t		time_to_sleep;
	uint64_t		time_last_meal;
	pthread_t		thread;
	pthread_mutex_t	mutex_left_fork;
	pthread_mutex_t	*mutex_right_fork;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*mutex_dead;
	struct s_env	*env;
}				t_philo;

typedef struct s_env
{
	long			num_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			n_must_eat;
	int				start;
	int				must_eat_flag;
	int				must_eat_all_finish;
	uint64_t		time_start;
	t_philo			*philo;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_dead;
	pthread_t		dead_checker;
}				t_env;

size_t		ft_strlen(const char *str);
int			ft_isnum(char *string);
long		ft_absatol(const char *string);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putchar_fd(char c, int fd);

void		ft_usleep(uint64_t miliseconds);
uint64_t	time_get_msec(uint64_t start);

int			args_checker(int argc, char **argv);
t_env		*args_getter(int argc, char **argv);

int			exit_error(t_env *env);
void		clear_all(t_env *env);
void		*kill_me(t_env *env, int i);
void		*dead_clean_exit(t_env *env);

int			philo_threads_create(t_env *env, int num_of_philo);
void		philo_threads_destroy(t_env *arg, int num_of_philos);
void		philo_threads_set_forks(t_philo *philo, int num_of_philos);
void		*philo_rutine(void *arg);
void		*philo_check_dead(t_env *env);
void		*philo_action_sleep(t_philo *philo);
void		*philo_action_eat(t_philo *philo);
void		*philo_action_think(t_philo *philo);
void		philo_take_fork(t_philo *philo);

void		print_messege(t_philo *philo, char *messege);
#endif