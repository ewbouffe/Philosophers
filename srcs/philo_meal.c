/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_meal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewbouffe <ewbouffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:56:13 by ewbouffe          #+#    #+#             */
/*   Updated: 2025/06/25 18:37:45 by ewbouffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	eat(t_philo *philo)
{
	long	meal_inter;
	bool	stop;

	stop = shall_we_stop(philo);
	if (stop == 1)
	{
		drop_forks(philo);
		return (stop);
	}
	meal_inter = time_inter(philo->data);
	if (is_philo_still_alive(philo, meal_inter))
		return (stop);
	philo->meals_eaten++;
	is_philo_done_eating(philo);
	printf("%ld philo %d is eating\n", time_inter(philo->data), philo->rank);
	philo->last_meal_time = meal_inter;
	precise_usleep(philo->data->tt_eat, philo);
	return (stop);
}

bool	is_philo_still_alive(t_philo *philo, long current)
{
	bool	stop;
	
	stop = 0;
	stop = shall_we_stop(philo);
	if (stop)
		return (stop);
	if (current - philo->last_meal_time > philo->data->tt_die)
	{
		pthread_mutex_lock(&philo->data->dead_philos);
		philo->data->dead_philo = 1;
		pthread_mutex_unlock(&philo->data->dead_philos);
		usleep(500);
		printf("%ld philo %d has died !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", time_inter(philo->data), philo->rank);
		stop = shall_we_stop(philo);
	}
	return (stop);
}

void	is_philo_done_eating(t_philo *philo)
{
	if (philo->meals_eaten == philo->data->number_o_time_to_eat)
	{
		pthread_mutex_lock(&philo->data->done_philos);
		philo->data->done_philo++;
		pthread_mutex_unlock(&philo->data->done_philos);
	}
}
