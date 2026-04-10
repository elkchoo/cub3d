/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoo <echoo@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 19:09:26 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/04/11 00:22:27 by echoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "cub3d.h"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static void	setup(t_data *data);

// The memory of the texture paths are owned by main. Unless a function calls
// shutdown itself, which should be avoided unless inconvenient, the ownership
// of the texture paths by main shall not be infringed.
int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		return (ft_dprintf(2, "Format: ./cub3d <map>\n"), 1);
	data.fd = open(argv[1], O_RDONLY);
	data.filename_len = ft_strlen(argv[1]);
	if (data.fd < 0)
		return (perror(argv[1]), 1);
	if (data.filename_len < 4 || ft_strncmp(argv[1] + data.filename_len - 4,
			".cub", 4))
		return (close(data.fd), ft_dprintf(2, "Invalid file format\n"), 1);
	setup(&data);
	if (!val_cub(&data))
		end_program(0, &data, NULL);
	printf("Valid cub\n");
	printf("NO: %s\n", data.n_texture);
	printf("SO: %s\n", data.s_texture);
	printf("EA: %s\n", data.e_texture);
	printf("WE: %s\n", data.w_texture);
	printf("F: %i, %i, %i\n", data.p_color[0].red, data.p_color[0].green, data.p_color[0].blue);
	printf("C: %i, %i, %i\n", data.p_color[1].red, data.p_color[1].green, data.p_color[1].blue);
	end_program(0, &data, NULL);
}

static void	setup(t_data *data)
{
	data->map = NULL;
	data->n_texture = NULL;
	data->s_texture = NULL;
	data->e_texture = NULL;
	data->w_texture = NULL;
	data->p_color[0].set = 0;
	data->p_color[1].set = 0;
}
