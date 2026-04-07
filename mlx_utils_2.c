/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoo <echoo@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 01:48:43 by elkan             #+#    #+#             */
/*   Updated: 2026/04/07 18:05:56 by echoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "libft.h"

#include <stdlib.h>
#include <sys/time.h>

void	delay(long miliseconds, t_pars *par);
void	end_program(t_pars *par, int code);

void	delay(long miliseconds, t_pars *par)
{
	struct timeval	*time;
	suseconds_t		init_time;

	time = malloc(sizeof(struct timeval));
	if (time == NULL)
		end_program(par, 1);
	gettimeofday(time, NULL);
	init_time = time->tv_usec + time->tv_sec * 1000000L;
	while (time->tv_usec + time->tv_sec * 1000000L - init_time < miliseconds)
	{
		gettimeofday(time, NULL);
	}
	free(time);
}

void	end_program(t_pars *par, int code)
{
	t_img		*images[6];
	static int	index = 0;

	images[0] = par->p_img;
	images[1] = par->w_img;
	images[2] = par->s_img;
	images[3] = par->c_img;
	images[4] = par->e_img;
	images[5] = par->a_img;
	while (index < 6)
	{
		if (images[index] && images[index]->img_ptr)
		{
			mlx_destroy_image(par->mlx, images[index]->img_ptr);
		}
		free(images[index++]);
	}
	ft_free_arrays(par->map);
	if (par->wind)
		mlx_destroy_window(par->mlx, par->wind);
	if (par->mlx)
		mlx_destroy_display(par->mlx);
	free(par->mlx);
	free(par);
	exit(code);
}
