/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:04:01 by hgu               #+#    #+#             */
/*   Updated: 2023/03/31 18:11:14 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	l;

	l = 0;
	while (l < len)
	{
		*((unsigned char *)b + l) = c;
		l++;
	}
	if (l == len)
		return (b);
	return (0);
}
