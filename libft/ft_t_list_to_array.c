/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_list_to_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoo <echoo@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 18:48:03 by elkan             #+#    #+#             */
/*   Updated: 2026/04/07 13:53:25 by echoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

void	*ft_t_list_to_array(t_list *list, size_t content_size)
{
	int		list_len;
	void	*to_return;
	int		index;

	if (list == NULL)
		return (NULL);
	list_len = ft_lstsize(list);
	to_return = malloc(list_len * content_size);
	if (to_return == NULL)
		return (NULL);
	index = 0;
	while (list)
	{
		ft_memcpy(to_return + index, list->content, content_size);
		list = list->next;
		index += content_size;
	}
	return (to_return);
}
