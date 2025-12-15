/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:24:12 by ftemori           #+#    #+#             */
/*   Updated: 2024/05/07 19:24:15 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_eat_lock_forks(t_philo *philo)
{
	if (!philo->right_fork || !philo->left_fork)
	{
		pthread_mutex_lock(philo->first_philo->stat_mutex);
		*(philo->first_philo->status) = -1;
		pthread_mutex_unlock(philo->first_philo->stat_mutex);
		return (1);
	}
	if (pthread_mutex_lock(philo->left_fork) != 0)
		return (1);
	if (pthread_mutex_lock(philo->right_fork) != 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

int	ft_eat(t_philo *philo)
{
	if (ft_eat_lock_forks(philo) != 0)
		return (1);
	message_print(philo, time_stamp(philo), 'e');
	pthread_mutex_lock(philo->last_meal_m);
	*(philo->last_meal) = time_stamp(philo);
	pthread_mutex_unlock(philo->last_meal_m);
	ft_usleep(philo->time_to_eat);
	*(philo->meals_eaten) += 1;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	ft_eat_right_lock_forks(t_philo *philo)
{
	if (!philo->right_fork || !philo->left_fork)
	{
		pthread_mutex_lock(philo->first_philo->stat_mutex);
		*(philo->first_philo->status) = -1;
		pthread_mutex_unlock(philo->first_philo->stat_mutex);
		return (1);
	}
	if (pthread_mutex_lock(philo->right_fork) != 0)
		return (1);
	if (pthread_mutex_lock(philo->left_fork) != 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	return (0);
}

int	ft_eat_right(t_philo *philo)
{
	if (philo->philo_num == 1)
	{
		printf("0 0 has taken a fork\n%i 0 died\n", philo->time_to_die);
		return (1);
	}
	if (ft_eat_right_lock_forks(philo) != 0)
		return (1);
	message_print(philo, time_stamp(philo), 'e');
	pthread_mutex_lock(philo->last_meal_m);
	*(philo->last_meal) = time_stamp(philo);
	pthread_mutex_unlock(philo->last_meal_m);
	ft_usleep(philo->time_to_eat);
	*(philo->meals_eaten) += 1;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	ft_think(t_philo *philo)
{
	message_print(philo, time_stamp(philo), 't');
	ft_usleep(1);
	return (0);
}
