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
