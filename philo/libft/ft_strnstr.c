/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:43:03 by hgu               #+#    #+#             */
/*   Updated: 2023/04/12 20:03:52 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (!needle[0])
		return ((char *)haystack);
	while (haystack[i] && ((i + ft_strlen(needle)) <= len))
	{
		if (!ft_strncmp(haystack + i, needle, ft_strlen(needle)))
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}
