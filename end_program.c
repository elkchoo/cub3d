/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 13:35:04 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/04/10 17:54:42 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

#include <stdlib.h>
#include <unistd.h>

void	end_program(int	status, t_data *data, char *err_msg)
{
	if (err_msg)
		ft_dprintf(2, err_msg);
	ft_free_all(4, data->n_texture, data->s_texture,
		data->w_texture, data->e_texture);
	ft_saf_free_arrays(&data->map);
	close(data->fd);
	exit(status);
}
