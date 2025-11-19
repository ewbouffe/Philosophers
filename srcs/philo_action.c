/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:05:46 by ewbouffe          #+#    #+#             */
/*   Updated: 2025/11/19 22:39:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	think(t_philo *philo)
{
	long	think_time;

	if (shall_we_stop(philo))
		return (true);
	safe_print(philo, "is thinking");
	think_time = (philo->data->tt_eat * 2 - philo->data->tt_sleep);
	if (think_time < 0)
		think_time = 0;
	if (think_time + philo->data->tt_eat + philo->data->tt_sleep
		>= philo->data->tt_die)
		think_time = 1;
	if (think_time > 0)
		usleep(think_time * 1000);
	return (false);
}

bool	sleep_philo(t_philo *philo)
{
	if (shall_we_stop(philo))
		return (true);
	safe_print(philo, "is sleeping");
	if (precise_usleep((long) philo->data->tt_sleep, philo) == false)
		return (true);
	return (false);
}

bool	shall_we_stop(t_philo *philo)
{
	bool	stop;

	pthread_mutex_lock(philo->data->dead_philos);
	stop = (philo->data->dead_philo == 1);
	pthread_mutex_unlock(philo->data->dead_philos);
	if (stop)
		return (true);
	pthread_mutex_lock(philo->data->done_philos);
	stop = (philo->data->done_philo == philo->data->number_of_philo);
	pthread_mutex_unlock(philo->data->done_philos);
	return (stop);
}

bool	precise_usleep(long duration, t_philo *philo)
{
	long	start;
	long	elapsed;

	start = get_time_in_ms();
	while (1)
	{
		if (shall_we_stop(philo))
			return (false);
		elapsed = get_time_in_ms() - start;
		if (elapsed >= duration)
			break ;
		usleep(1000);
	}
	return (true);
}
