/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:23:09 by ftemori           #+#    #+#             */
/*   Updated: 2024/05/07 19:23:11 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	time_stamp(t_philo *philo)
{
	long int		stamp;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	stamp = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - philo->start_time;
	return (stamp);
}

int	inputcheck(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (1);
	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	if (ft_atoi(av[1]) > 200 || ft_atoi(av[2]) < 60
		|| ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60
		|| (ac == 6 && ft_atoi(av[5]) < 1))
		return (1);
	return (0);
}

t_philo	*node_filler(t_philo *philo, int i, int ac, char **av)
{
	values_assigner(philo, ac, av, i);
	if (philo->philo_num > 200 \
		|| philo->time_to_die < 60
		|| philo->time_to_eat < 60 || philo->time_to_sleep < 60
		|| (ac == 6 && philo->num_of_meals < 1))
		return (NULL);
	philo->thread = malloc(sizeof(pthread_t));
	if (i == philo->philo_num - 1)
		philo->next_philo = NULL;
	else
		philo->next_philo = malloc(sizeof(t_philo));
	return (philo->next_philo);
}

void	time_filler(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	philo->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return ;
}

int	data_to_struct(t_philo *philo, int ac, char **av)
{
	int		i;
	t_philo	*temp;

	temp = philo;
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		temp->first_philo = philo;
		temp = node_filler(temp, i, ac, av);
		i++;
	}
	if (mutex_initializer(philo) != 0)
		return (1);
	return (0);
}
