/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 23:38:19 by hgu               #+#    #+#             */
/*   Updated: 2023/04/05 11:41:50 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*c_dst;
	unsigned char	*c_src;

	if (src == dst)
		return (dst);
	else if (src < dst)
	{
		c_dst = (unsigned char *)dst;
		c_src = (unsigned char *)src;
		while (len > 0)
		{
			*(c_dst + len - 1) = *(c_src + len - 1);
			len--;
		}
	}
	else
	{
		dst = ft_memcpy(dst, src, len);
	}
	return (dst);
}
