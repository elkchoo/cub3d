/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 19:30:28 by echoo             #+#    #+#             */
/*   Updated: 2026/04/09 19:12:43 by Elkan Choo       ###   ########.fr       */
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

// val_cub HAS to keep reading in order to skip newlines and detect when the
// map starts. As a result, it reads the first line of the map, making that
// first line inaccessible through get_next_line. So, that first line has
// to be passed into val_map. The data will later be freed in the loop, so
// strdup is necessary.

int	val_map(t_data *data, char *f_line)
{
	char	*line;
	char	*map_str;

	map_str = ft_strdup(f_line);
	line = get_next_line(data->fd);
	if (map_str == NULL)
		return (free(line), free(map_str), 0);
	while (line)
	{
		if (*line == '\n')
			return (free(map_str), free(line),
				ft_dprintf(2, "Error\nEmpty line in map\n"), 0);
		if (!check_chars(line, 0)
			|| !ft_merge_strings(&map_str, line))
			return (free(map_str), free(line), 0);
		free(line);
		line = get_next_line(data->fd);
	}
	data->map = ft_split(map_str, '\n');
	free(map_str);
	if (!check_chars(line, 1) || !data->map
		|| !val_map_cov((const char **)data->map))
		return (ft_free_arrays(data->map), 0);
	return (1);
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
			return (ft_dprintf(2, "Error\nInvalid characters in map\n"), 0);
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			p_count++;
		i++;
	}
	if (final && p_count != 1)
		return (ft_dprintf(2, "Error\nMap must have one player\n"), 0);
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
			if (!check_walled(map[index], lowest))
			{
				return (ft_dprintf(2, "Error\nWalls don't cover map\n"), 0);
				exit (1);
			}
		}
		index++;
	}
	return (check_border(map, index));
}

int	check_walled(const char *line, int index)
{
	if (!line[index])
	{
		if (!iswall(line[index - 1]))
			return (0);
	}
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
		// printf("wall: %c%c\nindex: %i\n", map[0][index], map[height - 1][index], index);
		if (!iswall(map[0][index]) || !iswall(map[height - 1][index]))
			return (ft_dprintf(2, "Error\nWalls don't cover map\n"), 0);
		index++;
	}
	return (1);
}
