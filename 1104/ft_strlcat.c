/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:11:31 by hyuim             #+#    #+#             */
/*   Updated: 2023/10/30 21:55:08 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = 0;
	while (*(dst + i))
	{
		i++;
	}
	while (*src && i + 1 < dstsize)
	{
		*(dst + i++) = *src++;
	}
	*(dst + i) = 0;
	if (len_dst < dstsize)
	{
		return (len_dst + len_src);
	}
	else
	{
		return (len_src + dstsize);
	}
}
