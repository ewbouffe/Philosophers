/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:33:52 by ewbouffe          #+#    #+#             */
/*   Updated: 2025/06/29 03:45:06 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	philos_thread_init(t_data *data)
{
	size_t	i;

	i = 0;
	
	// mutex_wait lock
	while(i < (size_t)data->number_of_philo)
	{
		if(pthread_create(&data->philosophers[i].thread, NULL, &routine, &data->philosophers[i]) != 0)
			perror("failed to create thread");
		i++;
	}
	// mutex_wait delock
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

	// lock & delock
	philo = (t_philo *)arg;
	while(1)
	{
		if (grab_forks(philo))
			return (NULL);
		if (eat(philo))
			return (NULL);
		if (sleep_philo(philo))
			return (NULL);
		if (think(philo))
			return (NULL);
		
	}
	return (NULL);
}

// bool	even_grab_fork(t_philo *philo)
// {
// 	if (shall_we_stop(philo))
// 		return (true);
// 	pthread_mutex_lock(philo->right_fork);
// 	printf("%ld %d has taken a fork\n",time_inter(philo->data), philo->rank);
// 	if (shall_we_stop(philo))
// 		return (pthread_mutex_unlock(philo->right_fork), true);
// 	pthread_mutex_lock(philo->left_fork);
// 	printf("%ld %d has taken a fork\n",time_inter(philo->data), philo->rank);
// 	if (shall_we_stop(philo))
// 	{
// 		pthread_mutex_unlock(philo->left_fork);
// 		pthread_mutex_unlock(philo->right_fork);
// 		return (true);
// 	}
// 	return (false);
// }

// bool	odd_grab_fork(t_philo *philo)
// {
// 	if (shall_we_stop(philo))
// 		return (true);
// 	pthread_mutex_lock(philo->left_fork);
// 	printf("%ld %d has taken a fork\n",time_inter(philo->data), philo->rank);
// 	if (shall_we_stop(philo))
// 	{
// 		pthread_mutex_unlock(philo->left_fork);
// 		return (true);
// 	}
// 	pthread_mutex_lock(philo->right_fork);
// 	printf("%ld %d has taken a fork\n",time_inter(philo->data), philo->rank);
// 	if (shall_we_stop(philo))
// 	{
// 		pthread_mutex_unlock(philo->right_fork);
// 		pthread_mutex_unlock(philo->left_fork);
// 		return (true);
// 	}
// 	return (false);
// }

bool	drop_forks(t_philo *philo)
{
	bool	stop;

	stop = shall_we_stop(philo);
	if (&philo->first_fork)
	{
		pthread_mutex_unlock(&philo->first_fork);
		// pthread_mutex_init(&philo->first_fork, NULL);
	}
	
	pthread_mutex_unlock(&philo->second_fork);
	return (stop);
}


bool	grab_forks(t_philo *philo)
{
	if (shall_we_stop(philo))
		return (true);
	pthread_mutex_lock(&philo->first_fork);
	printf("%ld %d has taken a fork\n",time_inter(philo->data), philo->rank);
	if (shall_we_stop(philo))
	{
		drop_forks(philo);
		return (true);
	}
	pthread_mutex_lock(&philo->second_fork);
	printf("%ld %d has taken a fork\n",time_inter(philo->data), philo->rank);
	if (shall_we_stop(philo))
	{
		drop_forks(philo);
		return (true);
	}
	return (false);
}