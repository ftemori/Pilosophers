/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:53:00 by ftemori           #+#    #+#             */
/*   Updated: 2024/05/09 21:53:02 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	other_mutexes(t_philo *philo)
{
	philo->stat_mutex = malloc(sizeof(pthread_mutex_t));
	philo->last_meal_m = malloc(sizeof(pthread_mutex_t));
	philo->meals_eaten_m = malloc(sizeof(pthread_mutex_t));
	philo->death_time_m = malloc(sizeof(pthread_mutex_t));
	if (!philo->stat_mutex || !philo->last_meal_m || \
		!philo->meals_eaten_m || !philo->death_time_m)
		return (1);
	if (pthread_mutex_init(philo->stat_mutex, NULL) != 0 || \
		pthread_mutex_init(philo->last_meal_m, NULL) != 0 || \
		pthread_mutex_init(philo->meals_eaten_m, NULL) != 0 || \
		pthread_mutex_init(philo->death_time_m, NULL) != 0)
		return (1);
	return (0);
}

int	mutex_initializer(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp)
	{
		philo->right_fork = malloc(sizeof(pthread_mutex_t));
		if (!philo->right_fork)
			return (1);
		if (pthread_mutex_init(philo->right_fork, NULL) != 0)
			return (1);
		if (other_mutexes(philo) != 0)
			return (1);
		philo = philo->next_philo;
		if (!philo)
		{
			if (tmp->index != 0)
				tmp->first_philo->left_fork = tmp->right_fork;
			break ;
		}
		philo->left_fork = tmp->right_fork;
		tmp = philo;
	}
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	message_print(philo, time_stamp(philo), 's');
	if (ft_usleep(philo->time_to_sleep) != 0)
		perror("ERROR in ft_sleep\n");
	return (0);
}
