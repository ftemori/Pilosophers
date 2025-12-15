/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:47:30 by ftemori           #+#    #+#             */
/*   Updated: 2024/05/09 21:47:33 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	first_half(t_philo *philo)
{
	if (one(philo, 'e') != 0)
		return (1);
	if (odd_threads(philo, 's', 0) != 0)
		return (1);
	if (even_threads(philo, 't', 0) != 0)
		return (1);
	if (one (philo, 's') != 0)
		return (1);
	if (odd_threads (philo, 't', 0) != 0)
		return (1);
	return (0);
}

int	second_half(t_philo *philo)
{
	if (even_threads(philo, 'e', 0) != 0)
		return (1);
	if (one(philo, 't') != 0)
		return (1);
	if (odd_threads(philo, 'e', 0) != 0)
		return (1);
	if (even_threads (philo, 's', 0) != 0)
		return (1);
	return (0);
}

int	odd_algo(t_philo *philo)
{
	while ((philo->num_of_meals == -1) || (*(philo->meals_eaten) < \
		philo->num_of_meals))
	{
		if (ft_status_check(philo) != 0)
			break ;
		if (first_half(philo) != 0)
			break ;
		if (ft_status_check(philo) != 0)
			break ;
		if (second_half(philo) != 0)
			break ;
	}
	*(philo->death_time) = time_stamp(philo);
	pthread_mutex_lock(philo->first_philo->stat_mutex);
	*(philo->first_philo->status) = -1;
	pthread_mutex_unlock(philo->first_philo->stat_mutex);
	return (0);
}

static int	ft_trim(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' && str[i + 1] <= '9' && str[i + 1] >= '0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = ft_trim(str);
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = (result * 10) + (str[i] - 48);
		else
			result = result + (str[i] - 48);
		i++;
	}
	return (sign * result);
}
