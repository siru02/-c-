/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:31:51 by hgu               #+#    #+#             */
/*   Updated: 2023/04/03 22:49:34 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp;
	size_t			index;

	tmp = (unsigned char *)s;
	index = 0;
	while (index < n)
	{
		if (tmp[index] == (unsigned char)c)
			return ((void *)(tmp + index));
		index++;
	}
	return (0);
}
