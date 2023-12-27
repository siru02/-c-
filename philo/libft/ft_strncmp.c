/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:02:47 by hgu               #+#    #+#             */
/*   Updated: 2023/04/04 17:39:59 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	num;

	num = 0;
	while (num < n)
	{
		if (s1[num] != s2[num])
			return ((unsigned char)s1[num] - (unsigned char)s2[num]);
		else if (!(unsigned char)s1[num] && !(unsigned char)s2[num])
			break ;
		num++;
	}
	return (0);
}
