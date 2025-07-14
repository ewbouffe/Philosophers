/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_meal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:56:13 by ewbouffe          #+#    #+#             */
/*   Updated: 2025/07/14 10:47:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	eat(t_philo *philo)
{
	long	meal_inter;

	if (shall_we_stop(philo))
		return (true);
	meal_inter = time_inter(philo->data);
	if (is_philo_still_alive(philo, meal_inter))
		return (true);
	philo->meals_eaten++;
	philo->last_meal_time = meal_inter;
	printf("%ld %d is eating\n", time_inter(philo->data), philo->rank);
	if (is_philo_done_eating(philo))
		return (true);
	if (precise_usleep(philo->data->tt_eat, philo) == false)
		return (true);
	return (false);
}

bool	is_philo_still_alive(t_philo *philo, long current)
{
	if (current - philo->last_meal_time > philo->data->tt_die)
	{
		pthread_mutex_lock(philo->data->dead_philos);
		philo->data->dead_philo = 1;
		pthread_mutex_unlock(philo->data->dead_philos);
		usleep(1000);
		printf("%ld %d died\n", time_inter(philo->data), philo->rank);
		return (true);
	}
	if (shall_we_stop(philo))
		return (true);
	return (false);
}

bool	is_philo_done_eating(t_philo *philo)
{
	if (philo->meals_eaten == philo->data->number_o_time_to_eat)
	{
		pthread_mutex_lock(philo->data->done_philos);
		philo->data->done_philo++;
		pthread_mutex_unlock(philo->data->done_philos);
	}
	if (shall_we_stop(philo))
		return (true);
	return (false);
}
