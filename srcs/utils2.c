/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:28:01 by marvin            #+#    #+#             */
/*   Updated: 2025/07/14 10:28:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	philo_build_malloc_error(t_data *data, ssize_t i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(data->philosophers[i].left_fork);
		free(data->philosophers[i].left_fork);
		i--;
	}
	printf("Malloc failed to allocate memory\n");
}

void	first_and_second_fork(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < (size_t)data->number_of_philo)
	{
		if (data->philosophers[i].rank % 2 == 0)
		{
			data->philosophers[i].first_fork
				= data->philosophers[i].right_fork;
			data->philosophers[i].second_fork
				= data->philosophers[i].left_fork;
		}
		else
		{
			data->philosophers[i].first_fork
				= data->philosophers[i].left_fork;
			data->philosophers[i].second_fork
				= data->philosophers[i].right_fork;
		}
		i++;
	}
}

void	*monitor(void *arg)
{
	t_data	*data;
	size_t	i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < (size_t)data->number_of_philo)
		{
			if (check_philo_death(data, i))
				return (NULL);
			if (shall_we_stop(&data->philosophers[i]))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	print_death(t_philo *philo)
{
	pthread_mutex_lock(philo->data->print_mutex);
	printf("%ld %d died\n", time_inter(philo->data), philo->rank);
	pthread_mutex_unlock(philo->data->print_mutex);
}

void	mutex_destroyer(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < (size_t)data->number_of_philo)
	{
		pthread_mutex_destroy(data->philosophers[i].left_fork);
		free(data->philosophers[i].left_fork);
		i++;
	}
	i = 0;
	while (i < (size_t)data->number_of_philo)
	{
		pthread_mutex_destroy(&data->philosophers[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(data->dead_philos);
	pthread_mutex_destroy(data->done_philos);
	pthread_mutex_destroy(data->print_mutex);
	free(data->dead_philos);
	free(data->done_philos);
	free(data->print_mutex);
}
