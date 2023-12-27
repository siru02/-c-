/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:35:53 by hgu               #+#    #+#             */
/*   Updated: 2023/04/03 21:05:45 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			index;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	index = 0;
	tmp1 = (unsigned char *)s1;
	tmp2 = (unsigned char *)s2;
	while (index < n)
	{
		if (tmp1[index] != tmp2[index])
		{
			return (tmp1[index] - tmp2[index]);
		}
		index++;
	}
	return (0);
}
