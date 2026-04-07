/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoo <echoo@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 19:09:26 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/04/08 00:23:20 by echoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "cub3d.h"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	t_data	vars;
	int		index;

	if (argc != 2)
		return (write(2, "Format: ./so_long <map>\n", 24), 1);
	vars.fd = open(argv[1], O_RDONLY);
	vars.filename_len = ft_strlen(argv[1]);
	if (vars.fd < 0)
		return (perror(argv[1]), 1);
	if (vars.filename_len < 4 ||
		ft_strncmp(argv[1] + vars.filename_len - 4, ".cub", 4))
		return (close(vars.fd), write(2, "Invalid file format\n", 20), 1);
	setup(&vars);
	if (!val_cub(&vars))
		return (close(vars.fd), 1);
	close(vars.fd);
}

void	setup(t_data *vars)
{
	vars->n_texture = NULL;
	vars->s_texture = NULL;
	vars->e_texture = NULL;
	vars->w_texture = NULL;
	vars->f_color.set = 0;
	vars->c_color.set = 0;
}
