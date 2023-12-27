/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 16:58:05 by hgu               #+#    #+#             */
/*   Updated: 2023/04/05 12:01:34 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	inspect(char ch, char const *set)
{
	size_t	idx;

	idx = 0;
	while (set[idx])
	{
		if (ch == set[idx])
			return (1);
		idx++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	size_t	f_idx;
	size_t	e_idx;

	f_idx = 0;
	e_idx = ft_strlen(s1);
	while ((f_idx < e_idx) && inspect(s1[f_idx], set))
	{
		f_idx++;
	}
	while (e_idx >= 0 && inspect(s1[e_idx - 1], set))
	{
		e_idx--;
	}
	s2 = ft_substr(s1, f_idx, e_idx - f_idx);
	return (s2);
}
