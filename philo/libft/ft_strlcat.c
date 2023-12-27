/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:08:15 by hgu               #+#    #+#             */
/*   Updated: 2023/04/04 20:47:39 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	idx;

	idx = 0;
	len = ft_strlen(dst);
	if (dstsize <= len)
		return (ft_strlen(src) + dstsize);
	while (src[idx] && (len + idx < dstsize - 1))
	{
		dst[len + idx] = src[idx];
		idx++;
	}
	dst[len + idx] = 0;
	return (ft_strlen(src) + len);
}
