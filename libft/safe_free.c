/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:59:38 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/04/10 17:46:56 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

void	saf_free(void **mem)
{
	free(*mem);
	*mem = NULL;
}

void	ft_saf_free_arrays(char ***array)
{
	size_t	index;

	if (*array == NULL)
		return ;
	index = 0;
	while ((*array)[index])
	{
		free((*array)[index]);
		index++;
	}
	free(*array);
	*array = NULL;
}
