/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoo <echoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 16:09:37 by echoo             #+#    #+#             */
/*   Updated: 2026/04/24 16:10:09 by echoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpop_node(t_list **list, int n, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*tmp;
	int		index;

	ptr = *list;
	if (n == 0)
	{
		*list = (*list)->next;
		ft_lstdelone(ptr, del);
	}
	else if (n > 0)
	{
		index = 0;
		while (index++ < n - 1)
			ptr = ptr->next;
		tmp = ptr->next;
		ptr->next = tmp->next;
		ft_lstdelone(tmp, del);
	}
}
