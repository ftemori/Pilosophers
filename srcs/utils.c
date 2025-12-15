/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:29:31 by ftemori           #+#    #+#             */
/*   Updated: 2024/05/07 19:29:34 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_free(t_philo *philo)
{
	t_philo	*tmp;

	while (philo)
	{
		tmp = philo->next_philo;
		free(philo->status);
		free(philo->last_meal);
		free(philo->meals_eaten);
		free(philo->death_time);
		free(philo->thread);
		free(philo->right_fork);
		free(philo->stat_mutex);
		free(philo->last_meal_m);
		free(philo->meals_eaten_m);
		free(philo->death_time_m);
		free(philo);
		philo = tmp;
	}
}

void	values_assigner(t_philo *philo, int ac, char **av, int i)
{
	philo->status = malloc(sizeof(int));
	philo->last_meal = malloc(sizeof(int));
	philo->meals_eaten = malloc(sizeof(int));
	philo->death_time = malloc(sizeof(long int));
	philo->index = i;
	*(philo->status) = 0;
	*(philo->last_meal) = -1;
	*(philo->meals_eaten) = 0;
	*(philo->death_time) = -1;
	philo->philo_num = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->left_fork = NULL;
	philo->right_fork = NULL;
	if (ac == 6)
		philo->num_of_meals = ft_atoi(av[5]);
	else
		philo->num_of_meals = -1;
	return ;
}

int	even_threads(t_philo *philo, char ac, int i)
{
	if ((philo->index % 2) == 0 && philo->index != i)
	{
		if (ac == 'e')
		{
			if (ft_eat_right(philo) != 0)
				return (1);
		}
		else if (ac == 't')
		{
			if (ft_think(philo) != 0)
				return (1);
		}
		else if (ac == 's')
		{
			if (ft_sleep(philo) != 0)
				return (1);
		}
	}
	return (0);
}

int	odd_threads(t_philo *philo, char ac, int i)
{
	if ((philo->index % 2) != 0 && philo->index != i)
	{
		if (ac == 'e')
		{
			if (ft_eat(philo) != 0)
				return (1);
		}
		else if (ac == 't')
		{
			if (ft_think(philo) != 0)
				return (1);
		}
		else if (ac == 's')
		{
			if (ft_sleep(philo) != 0)
				return (1);
		}
	}
	return (0);
}

int	even_algo(t_philo *philo)
{
	if ((philo->index % 2) != 0)
		ft_usleep(1);
	while ((philo->num_of_meals == -1) || (*(philo->meals_eaten) < \
		philo->num_of_meals))
	{
		if (ft_status_check(philo->first_philo) != 0)
			break ;
		even_threads(philo, 'e', -1);
		odd_threads(philo, 's', -1);
		if (ft_status_check(philo->first_philo) != 0)
			break ;
		odd_threads(philo, 't', -1);
		odd_threads(philo, 'e', -1);
		if (ft_status_check(philo->first_philo) != 0)
			break ;
		even_threads(philo, 's', -1);
		even_threads(philo, 't', -1);
	}
	pthread_mutex_lock(philo->first_philo->stat_mutex);
	*(philo->first_philo->status) = -1;
	pthread_mutex_unlock(philo->first_philo->stat_mutex);
	return (0);
}
