/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:05:46 by ewbouffe          #+#    #+#             */
/*   Updated: 2025/06/25 04:19:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	think(t_philo *philo)
{
	printf("%ld philo %d is thinking\n", time_inter(philo->data), philo->rank);
}

void	eat(t_philo *philo)
{
	long	meal_inter;

	meal_inter = time_inter(philo->data);
	if (meal_inter - philo->last_meal_time > (long)philo->data->tt_die)
	{
		printf("%ld philo %d has died\n", time_inter(philo->data), philo->rank);
		pthread_mutex_lock(&philo->data->dead_philos);
		philo->data->dead_philo = 1;
		pthread_mutex_unlock(&philo->data->dead_philos);
		return ;
	}
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->data->number_o_time_to_eat)
	{
		pthread_mutex_lock(&philo->data->done_philos);
		philo->data->done_philo++;
		pthread_mutex_unlock(&philo->data->done_philos);
	}
	printf("%ld philo %d is eating\n", time_inter(philo->data), philo->rank);
	philo->last_meal_time = meal_inter;
	precise_usleep(philo->data->tt_eat);
}


void	sleep_philo(t_philo *philo)
{
	printf("%ld philo %d is sleeping\n", time_inter(philo->data), philo->rank);
	precise_usleep((long) philo->data->tt_sleep);
}

bool	shall_we_stop(t_philo *philo)
{
	bool	stop;
	
	pthread_mutex_lock(&philo->data->dead_philos);
	pthread_mutex_lock(&philo->data->done_philos);
	stop = (philo->data->dead_philo == 1 || philo->data->done_philo == philo->data->number_of_philo);	
	pthread_mutex_unlock(&philo->data->dead_philos);
	pthread_mutex_unlock(&philo->data->done_philos);
	return (stop);
}

void precise_usleep(long duration)
{
    long start = get_time_in_ms();
    long elapsed;

    while (1)
    {
        elapsed = get_time_in_ms() - start;
        if (elapsed >= duration)
            break;
        usleep(250);
    }
}
