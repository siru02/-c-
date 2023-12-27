/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:08:43 by hgu               #+#    #+#             */
/*   Updated: 2023/03/31 17:57:49 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;
	size_t	i;

	i = 0;
	arr = (void *)malloc(size * count);
	if (!arr)
		return (0);
	while (i < size * count)
	{
		*((char *)arr + i) = 0;
		i++;
	}
	return (arr);
}
