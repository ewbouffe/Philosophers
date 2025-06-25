/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewbouffe <ewbouffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:33:52 by ewbouffe          #+#    #+#             */
/*   Updated: 2025/06/25 18:49:12 by ewbouffe         ###   ########.fr       */
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
		// if (shall_we_stop(philo))
		// 	return	(NULL);
		// think(philo);
		// if (philo->rank % 2 == 0)
		// {
		// 	if (shall_we_stop(philo))
		// 		return	(NULL);
		// 	even_grab_fork(philo);
		// }
		// else
		// {
		// 	if (shall_we_stop(philo))
		// 		return	(NULL);	
		// 	odd_grab_fork(philo);
		// }
		// if (shall_we_stop(philo))
		// 	return	(NULL);
		// eat(philo);
		// drop_forks(philo);
		// if (shall_we_stop(philo))
		// 	return	(NULL);
		// sleep_philo(philo);
		if (think(philo))
			return (NULL);
		if (philo->rank % 2 == 0)
		{
			if (even_grab_fork(philo))
				return (NULL);
		}
		else
		{
			if (odd_grab_fork(philo))
				return (NULL);
		}
		if (eat(philo))
			return (NULL);
		drop_forks(philo);
		if (sleep_philo(philo))
			return (NULL);
	}
	return (NULL);
}

bool	even_grab_fork(t_philo *philo)
{
	bool	stop;

	stop = 0;
	stop = shall_we_stop(philo);
	if (stop)
		return (stop);
	pthread_mutex_lock(philo->left_fork);
	stop = shall_we_stop(philo);
	if (!stop)
		printf("%ld philo %d has locked a fork\n",time_inter(philo->data), philo->rank);
	pthread_mutex_lock(philo->right_fork);
	stop = shall_we_stop(philo);
	if (!stop)
		printf("%ld philo %d has locked a fork\n",time_inter(philo->data), philo->rank);
	if (stop)
		drop_forks(philo);
	return (stop);
}

bool	odd_grab_fork(t_philo *philo)
{
	bool	stop;

	stop = 0;
	stop = shall_we_stop(philo);
	if (stop)
		return (stop);
	pthread_mutex_lock(philo->right_fork);
	stop = shall_we_stop(philo);
	if (!stop)
		printf("%ld philo %d has locked a fork\n",time_inter(philo->data), philo->rank);
	pthread_mutex_lock(philo->left_fork);
	stop = shall_we_stop(philo);
	if (!stop)
		printf("%ld philo %d has locked a fork\n",time_inter(philo->data), philo->rank);
	if (stop)
		drop_forks(philo);
	return (stop);
}

bool	drop_forks(t_philo *philo)
{
	bool	stop;

	stop = shall_we_stop(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (stop);
}