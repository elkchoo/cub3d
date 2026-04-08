/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:37:24 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/04/08 18:30:45 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "cub3d.h"

size_t	ft_map_len(char *str)
{
	size_t	count;

	count = 0;
	while (str[count] != '\n' && str[count])
		count++;
	return (count);
}

void	set_pos(t_pos *pos, int x, int y)
{
	pos->x = x;
	pos->y = y;
}

int	iswall(char c)
{
	if (c == ' ' || c == '1')
		return (1);
	return (0);
}
