/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:34:03 by ftemori           #+#    #+#             */
/*   Updated: 2024/05/07 19:34:05 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_usleep(int time)
{
	struct timeval	tv;
	struct timeval	tv1;
	long			start_time;
	long			current_time;

	gettimeofday(&tv, NULL);
	start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	while (1)
	{
		usleep(10);
		gettimeofday(&tv1, NULL);
		current_time = (tv1.tv_sec * 1000) + (tv1.tv_usec / 1000);
		if (current_time >= start_time + time)
			return (0);
	}
	return (1);
}

int	message_print(t_philo *philo, long int ti_st, char flag)
{
	pthread_mutex_lock(philo->first_philo->death_time_m);
	pthread_mutex_lock(philo->first_philo->stat_mutex);
	if (*(philo->first_philo->status) == -1)
	{
		pthread_mutex_unlock(philo->first_philo->stat_mutex);
		pthread_mutex_unlock(philo->first_philo->death_time_m);
		return (1);
	}
	pthread_mutex_unlock(philo->first_philo->stat_mutex);
	if (flag == 'e')
	{
		printf("%li %i has taken a fork\n", ti_st, philo->index);
		printf("%li %i has taken a fork\n", ti_st, philo->index);
		printf("%li %i is eating\n", ti_st, philo->index);
	}
	else if (flag == 't')
		printf("%li %i is thinking\n", ti_st, philo->index);
	else if (flag == 's')
		printf("%li %i is sleeping\n", ti_st, philo->index);
	else if (flag == 'd')
		printf("%li %i died\n", ti_st, philo->index);
	pthread_mutex_unlock(philo->first_philo->death_time_m);
	return (0);
}

int	eat_time_check(t_philo *philo)
{
	long int	current_time;
	long int	time_left;

	while (philo)
	{
		current_time = time_stamp(philo);
		time_left = 0;
		pthread_mutex_lock(philo->last_meal_m);
		if (*(philo->last_meal) != -1)
			time_left = *(philo->last_meal) + philo->time_to_die;
		pthread_mutex_unlock(philo->last_meal_m);
		if ((time_left != 0 && current_time > time_left) || \
			philo->first_philo->next_philo == NULL)
		{
			pthread_mutex_lock(philo->first_philo->stat_mutex);
			*(philo->status) = 1;
			pthread_mutex_unlock(philo->first_philo->stat_mutex);
			return (1);
		}
		philo = philo->next_philo;
	}
	return (0);
}

void	*ft_check(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *) tmp;
	while (1)
	{
		if (eat_time_check(philo) == 1)
			break ;
		pthread_mutex_lock(philo->stat_mutex);
		if (*(philo->status) != 0)
		{
			pthread_mutex_unlock(philo->stat_mutex);
			break ;
		}
		pthread_mutex_unlock(philo->stat_mutex);
	}
	return (NULL);
}

int	ft_police(t_philo *philo)
{
	pthread_t	*police;

	police = malloc(sizeof(pthread_t));
	pthread_create(police, NULL, ft_check, (void *) philo);
	pthread_join(*police, NULL);
	free(police);
	return (0);
}
