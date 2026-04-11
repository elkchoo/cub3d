/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoo <echoo@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 19:09:26 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/04/11 12:30:43 by echoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "cub3d.h"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// The memory of the texture paths are owned by main. Unless a function calls
// shutdown itself, which should be avoided unless inconvenient, the ownership
// of the texture paths by main shall not be infringed.
int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		return (ft_dprintf(2, "Format: ./cub3d <map>\n"), 1);
	if (!val_input(&data, argv[1]))
		end_program(1, &data, NULL);
	printf("Valid cub\n");
	printf("NO: %s\n", data.n_texture);
	printf("SO: %s\n", data.s_texture);
	printf("EA: %s\n", data.e_texture);
	printf("WE: %s\n", data.w_texture);
	printf("F: %i, %i, %i\n", data.p_color[0].red, data.p_color[0].green, data.p_color[0].blue);
	printf("C: %i, %i, %i\n", data.p_color[1].red, data.p_color[1].green, data.p_color[1].blue);
	end_program(0, &data, NULL);
}
