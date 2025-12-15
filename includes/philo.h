/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 21:19:59 by ftemori           #+#    #+#             */
/*   Updated: 2024/05/07 21:20:02 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				index;
	int				*status;
	int				philo_num;
	int				*last_meal;
	int				*meals_eaten;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	long int		*death_time;
	long int		start_time;
	pthread_t		*thread;
	pthread_mutex_t	*stat_mutex;
	pthread_mutex_t	*last_meal_m;
	pthread_mutex_t	*meals_eaten_m;
	pthread_mutex_t	*death_time_m;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_philo	*first_philo;
	struct s_philo	*next_philo;
}				t_philo;

// main
int			ft_status_check(t_philo *philo);
int			one(t_philo *philo, char ac);

// actions
int			ft_think(t_philo *philo);
int			ft_eat_right(t_philo *philo);
int			ft_eat(t_philo *philo);

// input check
int			data_to_struct(t_philo *philo, int ac, char **av);
int			inputcheck(int ac, char **av);
void		time_filler(t_philo *philo);
t_philo		*node_filler(t_philo *philo, int i, int ac, char **av);
long int	time_stamp(t_philo *philo);

// utils
int			even_algo(t_philo *philo);
int			odd_threads(t_philo *philo, char ac, int i);
int			even_threads(t_philo *philo, char ac, int i);
void		values_assigner(t_philo *philo, int ac, char **av, int i);
void		ft_free(t_philo *philo);

// police
int			ft_usleep(int time);
int			ft_police(t_philo *philo);
int			eat_time_check(t_philo *philo);
int			message_print(t_philo *philo, long int ti_st, char flag);
void		*ft_check(void *tmp);

// helper func
int			ft_atoi(const char *str);
int			odd_algo(t_philo *philo);

// mutexes
int			ft_sleep(t_philo *philo);
int			mutex_initializer(t_philo *philo);

#endif