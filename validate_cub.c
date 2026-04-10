/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoo <echoo@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:30:39 by echoo             #+#    #+#             */
/*   Updated: 2026/04/10 11:26:58 by echoo            ###   ########.fr       */
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

// All error checking functions (val_colors and process_color) will free
// colors, so colors is only freed after a successful operation.
void	get_color(t_col *tr, char *line, int *index)
{
	char	**colors;

	(*index)++;
	while (line[*index] == ' ' || line[*index] == '\n')
		(*index)++;
	colors = ft_split(line + *index, ',');
	if (!colors || !val_colors(colors))
	{
		ft_dprintf(2, "Error\nInvalid / missing color data\n");
		exit (1);
	}
	tr->red = process_color(colors[0], colors);
	tr->green = process_color(colors[1], colors);
	tr->blue = process_color(colors[2], colors);
	tr->set = 1;
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
