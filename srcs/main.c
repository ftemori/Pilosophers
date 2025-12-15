/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:22:44 by ftemori           #+#    #+#             */
/*   Updated: 2024/05/07 19:22:47 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	one(t_philo *philo, char ac)
{
	if (philo->index == 0)
	{
		if (ac == 'e')
		{
			if (ft_eat_right (philo) != 0)
				return (1);
		}
		else if (ac == 't')
		{
			if (ft_think (philo) != 0)
				return (1);
		}
		else if (ac == 's')
		{
			if (ft_sleep (philo) != 0)
				return (1);
		}
	}
	return (0);
}

int	ft_status_check(t_philo *philo)
{
	pthread_mutex_t	*mut;

	mut = philo->first_philo->stat_mutex;
	pthread_mutex_lock(mut);
	if (*(philo->first_philo->status) == -1)
	{
		pthread_mutex_unlock(mut);
		return (1);
	}
	while (philo)
	{
		if (*(philo->status) != 0)
		{
			pthread_mutex_unlock(mut);
			message_print(philo, time_stamp(philo), 'd');
			pthread_mutex_lock(mut);
			*(philo->first_philo->status) = -1;
			pthread_mutex_unlock(mut);
			return (1);
		}
		philo = philo->next_philo;
	}
	pthread_mutex_unlock(mut);
	return (0);
}

void	*lobby(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *) philo;
	if ((tmp->philo_num % 2) == 0)
	{
		even_algo(tmp);
	}
	else
	{
		odd_algo(tmp);
	}
	return (NULL);
}

int	operator(t_philo *philo)
{
	t_philo	*temp;

	temp = philo;
	while (temp)
	{
		time_filler(temp);
		pthread_create(temp->thread, NULL, lobby, (void *) temp);
		temp = temp->next_philo;
	}
	temp = philo;
	ft_police(temp);
	while (temp)
	{
		if (pthread_join(*temp->thread, NULL) != 0)
			perror("ERROR joining the threads\n");
		temp = temp->next_philo;
	}
	ft_free(philo);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (inputcheck(ac, av))
	{
		printf("Error: invalid input\n");
		return (1);
	}
	philo = malloc(sizeof(t_philo));
	if (!philo)
	{
		printf("Error: malloc failed\n");
		return (1);
	}
	if (data_to_struct(philo, ac, av) != 0)
	{
		free(philo);
		printf("Error: invalid input\n");
		return (1);
	}
	operator(philo);
	return (0);
}
