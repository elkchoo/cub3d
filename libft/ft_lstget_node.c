/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoo <echoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 16:08:56 by echoo             #+#    #+#             */
/*   Updated: 2026/04/24 16:09:21 by echoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns the nth object on the list, with 0 being the first object.
// Returns NULL if the list has < n elements
t_list	*ft_lstget_node(t_list *list, int n)
{
	int		index;

	index = 0;
	while (index < n)
	{
		if (list->next)
			list = list->next;
		else
			return (NULL);
	}
	return (list);
}
