/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 19:30:28 by echoo             #+#    #+#             */
/*   Updated: 2026/04/10 17:58:59 by Elkan Choo       ###   ########.fr       */
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
// to be passed into val_map. The data will later be freed in the gnl loop, and
// I don't need the map string to persist (I only need it to store map data and
// and then split it with ft_split), so it's convenient to use it as a map
// string. It also helps because if I shutdown, I will have to free the line in
// the gnl loop of the previous function.

int	val_map(t_data *data, char **map_str)
{
	char	*line;

	line = get_next_line(data->fd);
	while (line)
	{
		if (*line == '\n')
			return (saf_free((void **)&line),
				ft_dprintf(2, "Error\nEmpty line in map\n"), 0);
		if (!check_chars(line, 0)
			|| !ft_merge_strings(map_str, line))
			return (saf_free((void **)&line), 0);
		saf_free((void **)&line);
		line = get_next_line(data->fd);
	}
	data->map = ft_split(*map_str, '\n');
	if (!check_chars(line, 1) || !data->map
		|| !val_map_cov((const char **)data->map))
		return (0);
	return (1);
}

// If not final, adds up numbers of players. If final, checks that only one
// player is in the map
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
				return (ft_dprintf(2, "Error\nWalls don't cover map\n"), 0);
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
