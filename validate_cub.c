/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoo <echoo@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:30:39 by echoo             #+#    #+#             */
/*   Updated: 2026/04/08 23:52:35 by echoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int		elements_set(t_data *vars);
void	add_element(t_data *vars, char *line, int *index);
char	*get_texture(char *line, int *index);
void	get_color(t_col *tr, char *line, int *index);

int	val_cub(t_data *vars)
{
	char	*line;
	int		index;
	
	line = get_next_line(vars->fd);
	while (line)
	{
		index = 0;
		while (line[index] != '\0')
		{
			if (!elements_set(vars))
			{
				// while (*line == ' ')
				// 	line++;
				add_element(vars, line, &index);
			}
			else
				if (index || !val_map(vars))
					return (free(line), 0);
			index++;
		}
		free(line);
		line = get_next_line(vars->fd);
	}
	return (elements_set(vars));
}

// Returns 1 if all elements are set, 0 if not all elements are set.
int	elements_set(t_data *vars)
{
	if (vars->n_texture == NULL)
		return (0);
	if (vars->s_texture == NULL)
		return (0);
	if (vars->e_texture == NULL)
		return (0);
	if (vars->w_texture == NULL)
		return (0);
	if (vars->f_color.set == 0)
		return (0);
	if (vars->c_color.set == 0)
		return (0);
	return (1);
}

void	add_element(t_data *vars, char *line, int *index)
{
	if (ft_strncmp(line + *(index), "NO", 2))
		vars->n_texture = get_texture(line, index);
	if (ft_strncmp(line + *(index), "SO", 2))
		vars->s_texture = get_texture(line, index);
	if (ft_strncmp(line + *(index), "EA", 2))
		vars->e_texture = get_texture(line, index);
	if (ft_strncmp(line + *(index), "WE", 2))
		vars->w_texture = get_texture(line, index);
	if (ft_strncmp(line + *(index), "F", 2))
		get_color(&vars->f_color, line, index);
	if (ft_strncmp(line + *(index), "C", 2))
		get_color(&vars->f_color, line, index);
}

void	get_color(t_col *tr, char *line, int *index)
{
	char	**colors;
	int		color_code;

	(*index)++;
	while (line[*index])
		(*index)++;
	colors = ft_split(line + *index, ',');
	if (!colors)
		// call shutdown (TODO)
		return ;
	tr->set = 1;
	color_code = ft_atoi(colors[0]);
	if (0 <= color_code && color_code <= 255)
		// call shutdown (TODO)
		return ;
	tr->red = color_code;
	color_code = ft_atoi(colors[1]);
	if (0 <= color_code && color_code <= 255)
		// call shutdown (TODO)
		return ;
	tr->green = color_code;
	color_code = ft_atoi(colors[1]);
	if (0 <= color_code && color_code <= 255)
		// call shutdown (TODO)
		return ;
	tr->blue = color_code;
	ft_free_arrays(colors);
	while (line[*index] != ' ')
		(*index)++;
}

char	*get_texture(char *line, int *index)
{
	int		strlen;
	char	*tr;

	(*index) += 2;
	while (line[*index] == ' ')
		(*index)++;
	strlen = 0;
	while (line[*index + strlen] && line[*index + strlen] != ' ')
		strlen++;
	tr = ft_calloc(strlen + 1, 1);
	if (tr == NULL)
		//shutdown should be called, TODO
		return (NULL);
	ft_gnl_strlcpy(tr, line, strlen + 1);
	*index += strlen;
	return (tr);
}
