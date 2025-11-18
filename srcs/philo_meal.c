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
	if (shall_we_stop(philo))
		return (true);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	philo->last_meal_time = time_inter(philo->data);
	pthread_mutex_unlock(&philo->meal_mutex);
	safe_print(philo, "is eating");
	if (is_philo_done_eating(philo))
		return (true);
	if (precise_usleep(philo->data->tt_eat, philo) == false)
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
