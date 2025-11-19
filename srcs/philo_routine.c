/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:33:52 by ewbouffe          #+#    #+#             */
/*   Updated: 2025/11/19 22:44:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	philos_thread_init(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < (size_t)data->number_of_philo)
	{
		if (pthread_create(&data->philosophers[i].thread,
				NULL, &routine, &data->philosophers[i]) != 0)
			perror("failed to create thread");
		i++;
	}
	if (pthread_create(&data->monitor_thread,
			NULL, &monitor, data) != 0)
		perror("failed to create monitor thread");
	i = 0;
	while (i < (size_t)data->number_of_philo)
	{
		if (pthread_join(data->philosophers[i].thread, NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
	pthread_join(data->monitor_thread, NULL);
	mutex_destroyer(data);
	return ;
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = time_inter(philo->data);
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->rank % 2 == 0)
		usleep(1000);
	while (1)
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
	safe_print(philo, "has taken a fork");
	if (shall_we_stop(philo))
	{
		pthread_mutex_unlock(philo->first_fork);
		return (true);
	}
	pthread_mutex_lock(philo->second_fork);
	safe_print(philo, "has taken a fork");
	if (shall_we_stop(philo))
	{
		drop_forks(philo);
		return (true);
	}
	return (false);
}

bool	check_philo_death(t_data *data, size_t i)
{
	long	current;
	long	last_meal;

	current = time_inter(data);
	pthread_mutex_lock(&data->philosophers[i].meal_mutex);
	last_meal = data->philosophers[i].last_meal_time;
	pthread_mutex_unlock(&data->philosophers[i].meal_mutex);
	if (current - last_meal > data->tt_die)
	{
		pthread_mutex_lock(data->dead_philos);
		data->dead_philo = 1;
		pthread_mutex_unlock(data->dead_philos);
		print_death(&data->philosophers[i]);
		return (true);
	}
	return (false);
}
