/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoo <echoo@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 19:09:26 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/04/10 11:38:22 by echoo            ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		return (ft_dprintf(2, "Format: ./cub3d <map>\n"), 1);
	data.fd = open(argv[1], O_RDONLY);
	data.filename_len = ft_strlen(argv[1]);
	if (data.fd < 0)
		return (perror(argv[1]), 1);
	if (data.filename_len < 4 ||
		ft_strncmp(argv[1] + data.filename_len - 4, ".cub", 4))
		return (close(data.fd), ft_dprintf(2, "Invalid file format\n"), 1);
	setup(&data);
	if (!val_cub(&data))
		return (close(data.fd), 1);
	printf("Valid cub\n");
	printf("NO: %s\n", data.n_texture);
	printf("SO: %s\n", data.s_texture);
	printf("EA: %s\n", data.e_texture);
	printf("WE: %s\n", data.w_texture);
	printf("F: %i, %i, %i\n", data.f_color.red, data.f_color.green, data.f_color.blue);
	printf("C: %i, %i, %i\n", data.c_color.red, data.c_color.green, data.c_color.blue);
	close(data.fd);
}

static void	setup(t_data *data)
{
	data->n_texture = NULL;
	data->s_texture = NULL;
	data->e_texture = NULL;
	data->w_texture = NULL;
	data->f_color.set = 0;
	data->c_color.set = 0;
}
