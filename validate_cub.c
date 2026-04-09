/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:30:39 by echoo             #+#    #+#             */
/*   Updated: 2026/04/09 19:39:18 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int		elements_set(t_data *data);
void	add_element(t_data *data, char *line, int *index);
char	*get_texture(char *line, int *index);
void	get_color(t_col *tr, char *line, int *index);

int	val_cub(t_data *data)
{
	char	*line;
	int		index;
	int		map_val;

	map_val = 0;
	line = get_next_line(data->fd);
	while (line)
	{
		index = 0;
		while (line[index] != '\0' && line[index] != '\n')
		{
			if (line[index])
			{
				while (line[index] == '\n' || line[index] == ' ')
					index++;
				if (!elements_set(data))
				{
					if (line[index] == '\0')
						break ;
					add_element(data, line, &index);
				}
				else
				{
					if (!map_val && !val_map(data, line))
						return (free(line), 0);
					else
						map_val = 1;
				}
				if (line[index])
					index++;
			}
		}
		free(line);
		line = get_next_line(data->fd);
	}
	if (map_val == 0)
		return (ft_dprintf(2, "Error\nNo map\n"), 0);
	return (elements_set(data));
}

// Returns 1 if all elements are set, 0 if not all elements are set.
int	elements_set(t_data *data)
{
	if (data->n_texture == NULL)
		return (0);
	if (data->s_texture == NULL)
		return (0);
	if (data->e_texture == NULL)
		return (0);
	if (data->w_texture == NULL)
		return (0);
	if (data->f_color.set == 0)
		return (0);
	if (data->c_color.set == 0)
		return (0);
	return (1);
}

void	add_element(t_data *data, char *line, int *index)
{
	if (!ft_strncmp(line + *(index), "NO", 2))
		data->n_texture = get_texture(line, index);
	else if (!ft_strncmp(line + *(index), "SO", 2))
		data->s_texture = get_texture(line, index);
	else if (!ft_strncmp(line + *(index), "EA", 2))
		data->e_texture = get_texture(line, index);
	else if (!ft_strncmp(line + *(index), "WE", 2))
		data->w_texture = get_texture(line, index);
	else if (!ft_strncmp(line + *(index), "F", 1))
		get_color(&(data->f_color), line, index);
	else if (!ft_strncmp(line + *(index), "C", 1))
		get_color(&(data->c_color), line, index);
	else
	{
		ft_dprintf(2, "Error\nInvalid identifier\n");
		exit(1);
	}
}

// The color checking is very tricky. I need to parse the colors, and check
// that there are indeed 3 numbers. So, each string in split has to be checked
// for non-numbers. atoi cannot be trusted to do this. However, recall that
// since elements can be separated by spaces, the last one is allowed to have
// some in its later buffers. So, maybe the check stops when it sees spaces,
// sure. Maybe I can copy get_texture's solution where I measure a strlen that
// stops before any spaces or newlines, and I can also limit it to 4 since
// only up to 3 chars are valid (biggest number is 255), and a 4th char to
// see if a number bigger than that is given. So, perhaps a char [4], and
// then I copy from the number string into the array, until 4 chars or a space
// or newline is encountered, and then I check that everything is a digit, then
// I pass to atoi and do the number range checks. Man, validating the colors
// sucks
void	get_color(t_col *tr, char *line, int *index)
{
	char	**colors;
	int		color_code;

	(*index)++;
	while (line[*index] == ' ' || line[*index] == '\n')
		(*index)++;
	colors = ft_split(line + *index, ',');
	for (int i = 0; colors[i]; i++)
	{
		printf("color: %s\n", colors[i]);
	}
	if (!colors)
	{
		ft_dprintf(2, "Error\nColor data missing\n");
		exit (1);
	}
	tr->set = 1;
	if (!colors[0] || !colors[0][0])
	{
		ft_dprintf(2, "Error\nColor data missing\n");
		exit (1);
	}
	color_code = ft_atoi(colors[0]);
	if (color_code < 0 || 255 < color_code)
	{
		ft_dprintf(2, "Error\nInvalid color code\n");
		exit (1);
	}
	tr->red = color_code;
	if (!colors[1] || !colors[1][0])
	{
		ft_dprintf(2, "Error\nColor data missing\n");
		exit (1);
	}
	color_code = ft_atoi(colors[1]);
	if (color_code < 0 || 255 < color_code)
	{
		ft_dprintf(2, "Error\nInvalid color code\n");
		exit (1);
	}
	tr->green = color_code;
	if (!colors[2] || !colors[2][0])
	{
		ft_dprintf(2, "Error\nColor data missing\n");
		exit (1);
	}
	color_code = ft_atoi(colors[2]);
	if (color_code < 0 || 255 < color_code)
	{
		ft_dprintf(2, "Error\nInvalid color code\n");
		exit (1);
	}
	tr->blue = color_code;
	while (line[*index] && line[*index] != ' ')
		(*index)++;
	ft_free_arrays(colors);
}

char	*get_texture(char *line, int *index)
{
	int		strlen;
	char	*tr;

	(*index) += 2;
	while (line[*index] == ' ')
		(*index)++;
	if (!line[*index] || line[*index] == '\n')
	{
		ft_dprintf(2, "Error\nNo data after identifier\n");
		exit (1);
	}
	strlen = 0;
	while (line[*index + strlen] && line[*index + strlen] != ' ' &&
		line[*index + strlen] != '\n')
		strlen++;
	tr = ft_calloc(strlen + 1, 1);
	if (tr == NULL)
		//shutdown should be called, TODO
		return (NULL);
	ft_strlcpy(tr, line + *index, strlen + 1);
	*index += strlen;
	return (tr);
}
