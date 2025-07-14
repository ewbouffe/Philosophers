/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:34:03 by ewbouffe          #+#    #+#             */
/*   Updated: 2025/07/14 11:06:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sig;
	int	result;

	i = 0;
	sig = 1;
	result = 0;
	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sig *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		result = 10 * result + (str[i] - 48);
		i++;
	}
	return (result * sig);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*rep;
	size_t	i;

	if (nmemb && size > SIZE_MAX / nmemb)
		return (NULL);
	i = 0;
	rep = malloc(nmemb * size);
	if (!rep)
		return (NULL);
	while (i < nmemb * size)
		((unsigned char *)rep)[i++] = 0;
	return (rep);
}

long	time_inter(t_data *data)
{
	long	tn;
	if (!data)
	{
		fprintf(stderr, "NULL data in time_inter!\n");
		return (0);
	}
	tn = get_time_in_ms();
	return (tn - data->start_time);
}

long	get_time_in_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

void	mutex_destroyer(t_data *data)
{
    size_t  i;

    i = 0;
    while(i < (size_t)data->number_of_philo - 1)
    {
        pthread_mutex_destroy(data->philosophers[i].left_fork);
		free(data->philosophers[i].left_fork);
        i++;
    }
    pthread_mutex_destroy(data->dead_philos);
    pthread_mutex_destroy(data->done_philos);
	free(data->dead_philos);
	free(data->done_philos);
}