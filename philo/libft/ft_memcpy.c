/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 23:33:58 by hgu               #+#    #+#             */
/*   Updated: 2023/04/03 22:54:52 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	index;

	index = 0;
	if (src == dst)
		return (dst);
	while (index < n)
	{
		*((unsigned char *)dst + index) = *((unsigned char *)src + index);
		index++;
	}
	return (dst);
}
