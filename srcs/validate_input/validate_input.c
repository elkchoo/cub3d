/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoo <echoo@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:06:54 by echoo             #+#    #+#             */
/*   Updated: 2026/04/11 12:35:29 by echoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

static void	setup(t_data *data);

int	val_input(t_data *data, char *filename)
{
	data->fd = open(filename, O_RDONLY);
	data->filename_len = ft_strlen(filename);
	if (data->fd < 0)
		return (perror(filename), 1);
	if (data->filename_len < 4 || ft_strncmp(filename + data->filename_len - 4,
			".cub", 4))
		return (ft_dprintf(2, "Invalid file format\n"), 1);
	setup(data);
	if (val_cub(data))
		return (1);
	return (0);
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

int	iswall(char c)
{
	if (c == ' ' || c == '1')
		return (1);
	return (0);
}
