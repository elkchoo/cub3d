/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 19:30:28 by echoo             #+#    #+#             */
/*   Updated: 2026/04/08 13:31:07 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	check_chars(char *line, int final);
int	val_map_cov(const char **map);
int	check_walled(const char *line, int index);
int	check_border(const char **map, int height);

int	val_map(t_data *vars)
{
	char	*line;
	char	*map_str;

	map_str = ft_calloc(1, sizeof(char));
	line = get_next_line(vars->fd);
	if (map_str == NULL || line == NULL)
		return (free(line), free(map_str), write(2, "Error\nNo map\n", 13), 0);
	while (line)
	{
		if (*line == '\n' || check_chars(line, 0)
			|| !ft_merge_strings(&map_str, line))
			return (free(map_str), free(line), 0);
		free(line);
		line = get_next_line(vars->fd);
	}
	vars->map = ft_split(map_str, '\n');
	if (!check_chars(line, 1) || !vars->map || !val_map_cov(*vars->map))
		return (free(map_str), ft_free_arrays(vars->map), 0);
	return (free(map_str), 1);
}

// If not final, adds up numbers of exits, players, and collectibles.
int	check_chars(char *line, int final)
{
	static int	p_count = 0;
	int			i;

	i = 0;
	while (!final && line[i] && line[i] != '\n')
	{
		if (!(line[i] == '0' || line[i] == '1' || line[i] == 'N'
				|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W'
				|| line[i] == ' '))
			return (write(2, "Error\nInvalid characters in map\n", 32), 0);
		if (line[i] == 'P')
			p_count++;
		i++;
	}
	if (final && p_count != 1)
		return (write(2, "Error\nMap must have one player\n", 39), 0);
	return (1);
}

int	val_map_cov(const char **map)
{
	static int	index = 1;
	int			prev_len;
	int			next_len;
	int			line_len;
	int			lowest;

	while (map[index])
	{
		if (map[index + 1])
		{
			prev_len = ft_strlen(map[index - 1]);
			next_len = ft_strlen(map[index + 1]);
			line_len = ft_strlen(map[index]);
			lowest = prev_len;
			if (line_len < prev_len)
				lowest = line_len;
			if (next_len < prev_len)
				lowest = next_len;
			check_walled(map[index], lowest);
		}
		index++;
	}
	return (check_border(map, index));
}

int	check_walled(const char *line, int index)
{
	while (line[index])
	{
		if (!iswall(line[index]))
			return (0);
		index++;
	}
	return (1);
}

int	check_border(const char **map, int height)
{
	int	index;

	index = 0;
	while (map[0][index])
	{
		if (!iswall(map[0][index]) || !iswall(map[height - 1][index]))
			return (write(2, "Error\nWalls don't cover map\n", 27), 0);
		index++;
	}
	return (1);
}
