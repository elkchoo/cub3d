/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_steps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoo <echoo@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 22:10:32 by elkan             #+#    #+#             */
/*   Updated: 2026/04/07 17:29:51 by echoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "libft.h"

void	config_steps(t_pars *par, int step)
{
	if (step && par->steps < 4294967295)
	{
		par->steps++;
		ft_printf("Moves: %u\n", par->steps);
	}
}
