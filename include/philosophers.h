/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:34:15 by ewbouffe          #+#    #+#             */
/*   Updated: 2025/07/14 11:20:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include "struct.h"
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <stdbool.h>
#include <unistd.h>

//utils
int	ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
long	time_inter(t_data *data);
long	get_time_in_ms(void);
void	mutex_destroyer(t_data *data);

//parsing
void	main_parsing(t_data *data, int c, char **args);
void	is_numeric(t_data *data, char **args);
void	parsing_error_printer(t_data *data);

//data build
bool	struct_initiator(t_data *data, char **args);
bool	data_builder(t_data *data, char **args);
bool	philo_builder(t_data *data);
bool	create_and_assign_forks(t_data *data);
void	first_and_second_fork(t_data *data);

// philo routine
void	philos_thread_init(t_data *data);
void	*routine(void *arg);
bool	even_grab_fork(t_philo *philo);
bool	odd_grab_fork(t_philo *philo);
bool	drop_forks(t_philo *philo);
bool    grab_forks(t_philo *philo);
//philo action
bool	think(t_philo *philo);
bool	sleep_philo(t_philo *philo);
bool	shall_we_stop(t_philo *philo);
bool    precise_usleep(long duration, t_philo *philo);

//philo meal
bool	eat(t_philo *philo);
bool    is_philo_still_alive(t_philo *philo, long current);
bool    is_philo_done_eating(t_philo *philo);

//utils2
void	philo_build_malloc_error(t_data *data, ssize_t i);

#endif