/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoo <echoo@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:30:39 by echoo             #+#    #+#             */
/*   Updated: 2026/04/11 12:09:03 by echoo            ###   ########.fr       */
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
char	*get_texture(t_data *data, char *line, int *index);
int		val_cub(t_data *data);

int	val_cub(t_data *data)
{
	char	*line;
	int		index;

	line = get_next_line(data->fd);
	while (line)
	{
		index = 0;
		while (line[index] != '\0' && line[index] != '\n')
		{
			while (line[index] == ' ')
				index++;
			if (!elements_set(data))
				add_element(data, line, &index);
			else if (val_map(data, &line))
				return (saf_free((void **)&line), 1);
			else
				return (saf_free((void **)&line), 0);
			if (line[index])
				index++;
		}
		saf_free((void **)&line);
		line = get_next_line(data->fd);
	}
	return (0);
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
	if (data->p_color[0].set == 0)
		return (0);
	if (data->p_color[1].set == 0)
		return (0);
	return (1);
}

void	add_element(t_data *data, char *line, int *index)
{
	if (!ft_strncmp(line + *(index), "NO", 2))
		data->n_texture = get_texture(data, line, index);
	else if (!ft_strncmp(line + *(index), "SO", 2))
		data->s_texture = get_texture(data, line, index);
	else if (!ft_strncmp(line + *(index), "EA", 2))
		data->e_texture = get_texture(data, line, index);
	else if (!ft_strncmp(line + *(index), "WE", 2))
		data->w_texture = get_texture(data, line, index);
	else if (!ft_strncmp(line + *(index), "F", 1))
		get_color(data, 0, line, index);
	else if (!ft_strncmp(line + *(index), "C", 1))
		get_color(data, 1, line, index);
	else
	{
		saf_free((void **)&line);
		end_program(1, data, "Error\nInvalid identifier\n");
	}
}

// In the event of an error, line, which is malloc, must be freed here.
// If no error, line is owned by the previous function.
char	*get_texture(t_data *data, char *line, int *index)
{
	int		strlen;
	char	*tr;

	(*index) += 2;
	while (line[*index] == ' ')
		(*index)++;
	if (!line[*index] || line[*index] == '\n')
	{
		saf_free((void **)&line);
		end_program(1, data, "Error\nNo data after identifier\n");
	}
	strlen = 0;
	while (line[*index + strlen] && line[*index + strlen] != ' '
		&& line[*index + strlen] != '\n')
		strlen++;
	tr = ft_calloc(strlen + 1, 1);
	if (tr == NULL)
	{
		saf_free((void **)&line);
		end_program(1, data, NULL);
	}
	ft_strlcpy(tr, line + *index, strlen + 1);
	*index += strlen;
	return (tr);
}
