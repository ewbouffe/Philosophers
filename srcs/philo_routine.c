/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:33:52 by ewbouffe          #+#    #+#             */
/*   Updated: 2025/07/11 13:13:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	philos_thread_init(t_data *data)
{
	size_t	i;

	i = 0;
	
	while(i < (size_t)data->number_of_philo)
	{
		if(pthread_create(&data->philosophers[i].thread, NULL, &routine, &data->philosophers[i]) != 0)
			perror("failed to create thread");
		i++;
	}
	i = 0;
	while (i < (size_t)data->number_of_philo)
	{
		if (pthread_join(data->philosophers[i].thread, NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
	mutex_destroyer(data);
	return ;
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while(1)
	{
		if (grab_forks(philo))
			return (NULL);
		if (eat(philo))
		{
			drop_forks(philo);	
			return (NULL);
		}
		drop_forks(philo);
		if (sleep_philo(philo))
			return (NULL);
		if (think(philo))
			return (NULL);
	}
	return (NULL);
}

bool	drop_forks(t_philo *philo)
{
	bool	stop;

	stop = shall_we_stop(philo);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	return (stop);
}


bool	grab_forks(t_philo *philo)
{
	if (shall_we_stop(philo))
		return (true);
	pthread_mutex_lock(philo->first_fork);
	printf("%ld %d has taken a fork\n",time_inter(philo->data), philo->rank);
	if (shall_we_stop(philo))
	{
		pthread_mutex_unlock(philo->first_fork);
		return (true);
	}
	pthread_mutex_lock(philo->second_fork);
	printf("%ld %d has taken a fork\n",time_inter(philo->data), philo->rank);
	if (shall_we_stop(philo))
	{
		drop_forks(philo);
		return (true);
	}
	return (false);
}