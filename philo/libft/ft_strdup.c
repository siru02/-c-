/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:45:49 by hgu               #+#    #+#             */
/*   Updated: 2023/03/31 19:33:22 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*tmp;
	size_t	index;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	tmp = (char *)malloc(i + 1);
	index = 0;
	if (!tmp)
		return (0);
	while (s1[index])
	{
		tmp[index] = s1[index];
		index++;
	}
	tmp[index] = 0;
	return (tmp);
}
