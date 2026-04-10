/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 13:50:18 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/04/10 14:49:15 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>

void	ft_free_all(int num, ...)
{
	va_list	ap;
	int		index;
	void	*mem;

	va_start(ap, num);
	index = 0;
	while (index < num)
	{
		mem = va_arg(ap, void *);
		free(mem);
		index++;
	}
	va_end(ap);
}
