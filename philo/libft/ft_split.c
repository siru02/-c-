/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:59:24 by hgu               #+#    #+#             */
/*   Updated: 2023/04/12 20:03:40 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_seperator(char const *s, char c)
{
	int	idx;
	int	num;

	idx = 0;
	num = 0;
	if (!s[0])
		return (0);
	if (s[idx] == c)
		idx++;
	while (1)
	{
		if ((s[idx] == c || !s[idx]) && s[idx - 1] != c)
		{
			num++;
		}
		if (!s[idx])
			break ;
		idx++;
	}
	return (num);
}

static int	ft_free(char **split)
{
	int	word_idx;

	word_idx = 0;
	while (split[word_idx])
	{
		free(split[word_idx]);
		split[word_idx] = 0;
		word_idx++;
	}
	free(split);
	split = 0;
	return (1);
}

static void	ft_input_word(char *splits, int len, char const *word_stt, char c)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (i + flag < len)
	{
		if (word_stt[i + flag] == c)
		{
			flag++;
			continue ;
		}
		splits[i] = word_stt[i + flag];
		i++;
	}
	splits[i] = 0;
}

static int	ft_words(char const *s, char c, char **split)
{
	int		idx;
	int		len;
	int		word_idx;

	idx = 1;
	len = 0;
	word_idx = 0;
	if (s[idx - 1] != c)
		len++;
	while (idx <= (int)ft_strlen(s))
	{
		if ((!s[idx] || s[idx] == c) && s[idx - 1] != c)
		{
			split[word_idx] = (char *)malloc(len + 1);
			if (!split[word_idx])
			{
				return (ft_free(split));
			}
			ft_input_word(split[word_idx++], len, &s[idx - len], c);
			len = 0;
		}
		if (s[idx++] != c)
			len++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		word_index;
	int		word_num;
	int		fail;

	fail = 0;
	word_index = 0;
	word_num = count_seperator(s, c);
	split = (char **)malloc((sizeof(char *)) * (word_num + 1));
	if (!split || !s)
		return (0);
	split[word_num] = 0;
	if (s[0])
		fail = ft_words(s, c, split);
	if (fail)
		return (0);
	return (split);
}
