/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoo <echoo@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:03:48 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/04/10 11:25:19 by echoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

#include <stdlib.h>

// This val_colors function is made to catch three errors:

// Firstly, if there is less than
// three color data strings provided. If so, then c will not be 2, and return
// (c == 2) checks this.

// Secondly, if any of the color data strings are empty.
// This program zeroes buf[5], and copies up to 4 chars into buf. If the color
// data string is empty, then the first char contains a space or newline, and
// b will not be advanced again, so if (b == 0) checks this.

// It is necessary to not copy any spaces or newlines into the buf, as they
// are not digits and will fail the digit check, but they are allowed after the
// third color. Technically, this causes the program to wrongly pass if a space
// is found after the first or second color, but the subject explicitly stated
// that we did not have to handle spaces in the color input, so it's fine.

// Third, if any of the color data strings contain non-digits. This is checked
// by the loop where ft_isdigit is called. Conveniently, this also eliminates
// negative numbers, since '-' is not a digit. However, it will not eliminate
// numbers that are out of range.

// Althought it can detect 4 digit numbers, I think it's better for the number
// check with atoi to eliminate it later instead for more precise error
// handling. So, why check for 4 chars at all? The answer is to detect if a
// non-digit is added after three digits. If this isn't checked, it would pass
// atoi, and be accepted as valid. Now, I don't need to check more, since if
// the 4th char is a digit, it will fail atoi, and the 4th digit, and if it's
// not a digit, it will fail the digit check, so checking 4 chars is enough.

/**
 * @brief Function checks if the given color array is valid. If it is not,
 * the function frees colors. 
 * @param colors The char **array containing color data
 * @return Returns 1 if the colors are valid, 0 if not
*/
int	val_colors(char **colors)
{
	int		c;
	int		b;
	char	buf[5];

	c = -1;
	while (colors[++c] && c < 3)
	{
		ft_bzero(buf, 5);
		b = -1;
		while (colors[c][++b] && colors[c][b] != ' ' && colors[c][b] != '\n'
			&& b < 4)
			buf[b] = colors[c][b];
		if (b == 0)
			return (ft_free_arrays(colors), 0);
		b = -1;
		while (buf[++b])
			if (!ft_isdigit(buf[b]))
				return (ft_free_arrays(colors), 0);
	}
	if (c == 2)
		return (ft_free_arrays(colors), 0);
	return (1);
}

// As you recall, negative numbers are caught by val_color, so this funcion
// only needs to check for color codes that are too big.

/**
 * @brief Function checks if the given color code is valid. If it is not,
 * the function frees colors. If it is, it returns the color code as an
 * int to tbe stored.
 * @param code The color code to verify.
 * @param colors The char **array containing color data
 * @return Returns 1 if the colors are valid, 0 if not
*/

int	process_color(char *code, char **colors)
{
	int		color_code;

	color_code = ft_atoi(code);
	if (255 < color_code)
	{
		ft_free_arrays(colors);
		ft_dprintf(2, "Error\nInvalid color code\n");
		exit (1);
	}
	return (color_code);
}
