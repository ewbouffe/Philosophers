/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:05:46 by ewbouffe          #+#    #+#             */
/*   Updated: 2025/07/14 11:32:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	think(t_philo *philo)
{
	if (shall_we_stop(philo))
		return (true);
	printf("%ld %d is thinking\n", time_inter(philo->data), philo->rank);
	// usleep(1000);
	return (false);
}

bool	sleep_philo(t_philo *philo)
{
	if (shall_we_stop(philo))
		return (true);
	printf("%ld %d is sleeping\n", time_inter(philo->data), philo->rank);
	if (precise_usleep((long) philo->data->tt_sleep, philo) == false)
		return (true);
	return (false);
}

bool	shall_we_stop(t_philo *philo)
{
	bool	stop;
	
	stop = 0;
	pthread_mutex_lock(philo->data->dead_philos);
	pthread_mutex_lock(philo->data->done_philos);
	stop = (philo->data->dead_philo == 1 || philo->data->done_philo == philo->data->number_of_philo);
	pthread_mutex_unlock(philo->data->dead_philos);
	pthread_mutex_unlock(philo->data->done_philos);
	return (stop);
}

bool precise_usleep(long duration, t_philo *philo)
{
	long start = get_time_in_ms();
	long	elapsed;

	while (1)
	{
		if (shall_we_stop(philo))
			return (false);
		elapsed = get_time_in_ms() - start;
		if (elapsed >= duration)
			break;
		usleep(1000);
	}
	return (true);
}
