/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:44:30 by hgu               #+#    #+#             */
/*   Updated: 2023/04/02 22:44:56 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = 0;
	if (dstsize)
	{
		while (len < dstsize - 1)
		{
			if (!src[len])
				break ;
			dst[len] = src[len];
			len++;
		}
		dst[len] = 0;
	}
	len = 0;
	while (src[len])
		len++;
	return (len);
}
