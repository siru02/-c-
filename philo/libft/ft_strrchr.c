/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:27:11 by hgu               #+#    #+#             */
/*   Updated: 2023/04/04 21:00:55 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ch;
	int		index;

	ch = 0;
	index = 0;
	while (s[index])
	{
		if (s[index] == (unsigned char)c)
			ch = (char *)s + index;
		index++;
	}
	if (s[index] == (unsigned char)c)
		ch = (char *)s + index;
	return (ch);
}
