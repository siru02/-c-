/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 16:32:53 by hgu               #+#    #+#             */
/*   Updated: 2023/04/04 19:15:27 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	index;
	size_t	s_len;

	index = 0;
	s_len = ft_strlen(s);
	if (s_len == 0 || (size_t)start >= s_len)
		len = 0;
	else if (s_len - start < len)
		len = s_len - start;
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	while (index < len)
	{
		str[index] = s[start + index];
		index++;
	}
	str[index] = 0;
	return (str);
}
