/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 19:09:26 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/04/09 19:12:43 by Elkan Choo       ###   ########.fr       */
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
