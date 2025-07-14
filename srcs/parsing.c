/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:33:55 by ewbouffe          #+#    #+#             */
/*   Updated: 2025/07/14 10:27:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	main_parsing(t_data *data, int c, char **args)
{
	data->number_of_args = c;
	if (c < 5)
		data->parsing_error = 2;
	if (c > 6)
		data->parsing_error = 3;
	is_numeric(data, args);
}

void	is_numeric(t_data *data, char **args)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (i < (size_t)data->number_of_args)
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] < '0' || args[i][j] > '9')
				data->parsing_error = 1;
			j++;
		}
		i++;
	}
}

void	parsing_error_printer(t_data *data)
{
	if (data->parsing_error == 2)
		write(2, "Insufficient amount of parameters !!!\n", 39);
	if (data->parsing_error == 1)
		write(2, "Invalid parameters given !!!\n", 30);
	if (data->parsing_error == 3)
		write(2, "Too many parameters !!!\n", 25);
}
