/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:34:15 by ewbouffe          #+#    #+#             */
/*   Updated: 2025/06/25 04:15:17 by marvin           ###   ########.fr       */
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
void	data_builder(t_data *data, char **args);
void	philo_builder(t_data *data);
void	create_and_assign_forks(t_data *data);

// philo routine
void	philos_thread_init(t_data *data);
void	*routine(void *arg);
void	even_grab_fork(t_philo *philo);
void	odd_grab_fork(t_philo *philo);
void	drop_forks(t_philo *philo);

//philo action
void	think(t_philo *philo);
void	eat(t_philo *philo);
void	sleep_philo(t_philo *philo);
bool	shall_we_stop(t_philo *philo);
void precise_usleep(long duration);

void	printf_debug(void);

#endif