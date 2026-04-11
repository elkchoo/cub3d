/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoo <echoo@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 13:35:04 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/04/11 12:40:59 by echoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

#include <stdlib.h>
#include <unistd.h>

/* frees the following:
	char	**map;
	int		fd;
	char	*n_texture;
	char	*s_texture;
	char	*e_texture;
	char	*w_texture;
*/
void	free_val_data(t_data *data)
{
	ft_free_all(4, data->n_texture, data->s_texture,
		data->w_texture, data->e_texture);
	ft_saf_free_arrays(&data->map);
	close(data->fd);
}

void	end_program(int status, t_data *data, char *err_msg)
{
	if (err_msg)
		ft_dprintf(2, err_msg);
	free_val_data(data);
	exit(status);
}
