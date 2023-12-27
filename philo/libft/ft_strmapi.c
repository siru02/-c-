/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:37:53 by hgu               #+#    #+#             */
/*   Updated: 2023/04/04 17:38:20 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	idx;
	size_t			len;
	char			*str;

	idx = 0;
	len = 0;
	while (s[len])
		len++;
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	while (idx < len)
	{
		str[idx] = f(idx, s[idx]);
		idx++;
	}
	str[idx] = 0;
	return (str);
}
