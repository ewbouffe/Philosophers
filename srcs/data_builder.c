/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:34:12 by ewbouffe          #+#    #+#             */
/*   Updated: 2025/06/29 01:21:00 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	struct_initiator(t_data *data, char **args)
{
	data_builder(data, args);
	if (data->number_of_philo == 1)
	{
		printf("%ld 1 has taken a fork\n", time_inter(data));
		usleep(data->tt_die);
		printf("%ld 1 died\n", time_inter(data));
		return (false);
	}
	philo_builder(data);
	return (true);
}

void	data_builder(t_data *data, char **args)
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
}

void	philo_builder(t_data *data)
{
	size_t	i;

	i = 0;
	data->philosophers = ft_calloc(data->number_of_philo, sizeof(struct s_philosophers));
	if (!data->philosophers)
		return ;
	while (i < (size_t)data->number_of_philo)
	{
		data->philosophers[i].rank = i + 1;
		data->philosophers[i].data = data;
		i++;
	}
	create_and_assign_forks(data);
}

void	create_and_assign_forks(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < (size_t)data->number_of_philo)
	{
		data->philosophers[i].left_fork = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(data->philosophers[i].left_fork, NULL);
		i++;
	}
	i = 0;
	while(i < (size_t)data->number_of_philo - 1)
	{
		data->philosophers[i].right_fork = data->philosophers[i + 1].left_fork;
		i++;
	}
	data->philosophers[data->number_of_philo - 1].right_fork = data->philosophers[0].left_fork;
}
