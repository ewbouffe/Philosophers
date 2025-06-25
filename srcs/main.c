/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewbouffe <ewbouffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:34:06 by ewbouffe          #+#    #+#             */
/*   Updated: 2025/06/25 17:34:03 by ewbouffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int c, char **v)
{
	t_data data;

	if (v[1][0] == '0')
	{
		printf("Can't work with 0 philosophers\n");
		return (0);
	}
	memset(&data, 0, sizeof(struct s_data));
	main_parsing(&data, c, v);
	if (data.parsing_error != 0)
	{
		parsing_error_printer(&data);
		return (1);
	}
	if (!struct_initiator(&data, v))
		return (0);
	philos_thread_init(&data);
	free(data.philosophers);
	return (0);
}
