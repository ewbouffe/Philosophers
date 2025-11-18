/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewbouffe <ewbouffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:34:12 by ewbouffe          #+#    #+#             */
/*   Updated: 2025/11/18 12:21:03 by ewbouffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	struct_initiator(t_data *data, char **args)
{
	if (!data_builder(data, args))
		return (false);
	if (data->number_of_philo == 1)
	{
		printf("%ld 1 has taken a fork\n", time_inter(data));
		usleep(data->tt_die);
		printf("%ld 1 died\n", time_inter(data));
		pthread_mutex_destroy(data->dead_philos);
		pthread_mutex_destroy(data->done_philos);
		pthread_mutex_destroy(data->print_mutex);
		free(data->dead_philos);
		free(data->done_philos);
		free(data->print_mutex);
		return (false);
	}
	if (!philo_builder(data))
		return (false);
	return (true);
}

bool	data_builder(t_data *data, char **args)
{
	data->number_of_philo = ft_atoi(args[1]);
	data->tt_die = ft_atoi(args[2]);
	data->tt_eat = ft_atoi(args[3]);
	data->tt_sleep = ft_atoi(args[4]);
	if (data->number_of_args == 6)
		data->number_o_time_to_eat = ft_atoi(args[5]);
	else if (data->number_of_args == 5)
		data->number_o_time_to_eat = -1;
	data->start_time = get_time_in_ms();
	data->dead_philos = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!data->dead_philos)
	{
		printf("Malloc failed to allocate memory\n");
		return (false);
	}
	data->done_philos = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!data->done_philos)
	{
		printf("Malloc failed to allocate memory\n");
		free(data->dead_philos);
		return (false);
	}
	data->print_mutex = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!data->print_mutex)
	{
		printf("Malloc failed to allocate memory\n");
		free(data->dead_philos);
		free(data->done_philos);
		return (false);
	}
	pthread_mutex_init(data->dead_philos, NULL);
	pthread_mutex_init(data->done_philos, NULL);
	pthread_mutex_init(data->print_mutex, NULL);
	return (true);
}

bool	philo_builder(t_data *data)
{
	size_t	i;

	i = 0;
	data->philosophers = ft_calloc(data->number_of_philo, sizeof(struct s_philosophers));
	if (!data->philosophers)
		return (false);
	while (i < (size_t)data->number_of_philo)
	{
		data->philosophers[i].rank = i + 1;
		data->philosophers[i].data = data;
		pthread_mutex_init(&data->philosophers[i].meal_mutex, NULL);
		i++;
	}
	if (!create_and_assign_forks(data))
		return (false);
	return (true);
}

bool	create_and_assign_forks(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < (size_t)data->number_of_philo)
	{
		data->philosophers[i].left_fork = ft_calloc(1, sizeof(pthread_mutex_t));
		if (!data->philosophers[i].left_fork)
		{
			philo_build_malloc_error(data, (ssize_t)i--);
			return (false);
		}
		pthread_mutex_init(data->philosophers[i].left_fork, NULL);
		i++;
	}
	i = 0;
	while (i < (size_t)data->number_of_philo)
	{
		data->philosophers[i].right_fork = data->philosophers[(i + 1) % data->number_of_philo].left_fork;
		i++;
	}
	first_and_second_fork(data);
	return (true);
}

void	first_and_second_fork(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < (size_t)data->number_of_philo)
	{
		if (data->philosophers[i].rank % 2 == 0)
		{
			data->philosophers[i].first_fork = data->philosophers[i].right_fork;
			data->philosophers[i].second_fork = data->philosophers[i].left_fork;
		}
		else
		{
			data->philosophers[i].first_fork = data->philosophers[i].left_fork;
			data->philosophers[i].second_fork = data->philosophers[i].right_fork;
		}
		i++;
	}
}