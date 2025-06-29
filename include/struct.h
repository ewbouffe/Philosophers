/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:34:18 by ewbouffe          #+#    #+#             */
/*   Updated: 2025/06/29 03:17:43 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

typedef struct s_data t_data;
typedef struct s_philosophers t_philo;

typedef	struct s_philosophers
{
	long	last_meal_time;
	int	rank;
	int	meals_eaten;
	pthread_mutex_t	first_fork;
	pthread_mutex_t	second_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t	thread;
	t_data *data;
}t_philo;

typedef	struct s_data
{
	long	start_time;
	int	parsing_error;
	int	number_of_philo;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	number_o_time_to_eat;
	pthread_mutex_t	dead_philos;
	int	dead_philo;
	pthread_mutex_t	done_philos;
	int	done_philo;
	int	number_of_args;
	t_philo *philosophers;
}t_data;


#endif