/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoo <echoo@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 13:12:23 by elkan             #+#    #+#             */
/*   Updated: 2026/04/10 11:24:14 by echoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define _USE_MATH_DEFINES

# include <stddef.h>

// Defines are HARD CODED. DO NOT TOUCH

# define BONUS 0

// Determines pixel size.
# define SIZE 40

// Determines how many frames it takes to move.
# define FRAMES 10

typedef struct coordinates
{
	int	x;
	int	y;
}	t_pos;

typedef struct img
{
	void	*img_ptr;
	int		x;
	int		y;
}	t_img;

typedef struct color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	unsigned char	set;
}	t_col;

typedef struct main_data
{
	int		filename_len;
	char	**map;
	int		fd;
	char	*n_texture;
	char	*s_texture;
	char	*e_texture;
	char	*w_texture;
	t_col	f_color;
	t_col	c_color;
}	t_data;

typedef struct parameters
{
	void			*mlx;
	void			*wind;
	char			**map;
	int				width;
	int				height;
	unsigned int	steps;
	char			steps_str[17];
	int				cols;
	int				redraw;
	unsigned char	p_rot;
	t_img			*a_img;
	t_img			*p_img;
	t_img			*w_img;
	t_img			*s_img;
	t_img			*c_img;
	t_img			*e_img;
	t_pos			p_pos;
	t_pos			e_pos;
}	t_pars;

// from check_path.c
int		check_path(char **map, int width, int height, int cols);

// from search_path.c
int		search_path(char **map, t_pos p_pos, int cols);

// from cub3d_utils.c
size_t	ft_map_len(char *str);
void	set_pos(t_pos *pos, int x, int y);
/**
 * @return Returns 1 if c is a wall, 0 if not
*/
int		iswall(char c);

// from open_window.c
int		open_window(char **map, int width, int height, int cols);

// from mlx_utils.c
int		handle_keys(int keycode, void *p_ptr);
int		close_window(void *p_ptr);
void	move_player(t_pars *par, unsigned char move_no);
void	check_end(t_pars *par);
void	draw_and_set_pos(t_pars *par, char c, int x, int y);

// from mlx_utlis_2.c
void	delay(long miliseconds, t_pars *par);
void	end_program(t_pars *par, int code);

// from player_rotation.c
void	player_rotation(t_pars *par, unsigned char move_no);

// from player_movement.c
void	move(unsigned char move_no, t_pars *par);

// from config_steps.h or config_steps_bonus.h
void	config_steps(t_pars *par, int step);

// from validate_map.c
/**
 * @return Returns 1 if map is valid, 0 if not
*/
int		val_map(t_data *data, char *line);

// from validate_cub.c
/**
 * @return Returns 1 if cub is valid, 0 if not
*/
int		val_cub(t_data *data);

// from validate_colors.c

/**
 * @param colors The char **array containing color data
 * @return Returns 1 if the colors are valid, 0 if not
*/
int		val_colors(char **colors);

/**
 * @brief Function checks if the given color code is valid. If it is not,
 * the function frees colors. If it is, it returns the color code as an
 * int to tbe stored.
 * @param code The color code to verify.
 * @param colors The char **array containing color data
 * @return Returns 1 if the colors are valid, 0 if not
*/
int	process_color(char *code, char **colors);

#endif
