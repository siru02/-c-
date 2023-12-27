/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 16:41:36 by hgu               #+#    #+#             */
/*   Updated: 2023/04/05 11:43:41 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	len;
	size_t	len1;
	size_t	len2;

	s3 = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
		return (0);
	len = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	while (len < len1)
	{
		s3[len] = s1[len];
		len++;
	}
	len = 0;
	while (len < len2)
	{
		s3[len + len1] = s2[len];
		len++;
	}
	s3[len + len1] = 0;
	return (s3);
}
