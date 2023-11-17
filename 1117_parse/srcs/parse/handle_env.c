/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:29:34 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/17 15:45:08 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*insert_envp(t_token *token, char *tmp, char *str, int start)
{
	char	*new;
	int		new_len;
	int		str_len;

	if (tmp[0] == '\0')
		tmp[0] = '\0';
	str_len = ft_strlen(str);
	token->quote_end += str_len;
	new_len = ft_strlen(tmp) + str_len + 1;
	new = malloc(new_len);
	if (new == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(new, tmp, start + 1);
	if (token->flag == 1)
		split_after_expansion(token, str, new, tmp);
	else
	{
		ft_strlcat(new, str, new_len);
		ft_strlcat(new, tmp + start, new_len);
	}
	free(tmp);
	token->expansion_idx = start + str_len;
	return (new);
}

int	cut_env_idx(t_token *token, char *value, int idx)
{
	int	end_point;

	end_point = idx;
	while (value[++end_point])
	{
		if (expansion_separator(value[end_point]))
			break ;
		if (end_point == token->quote_end)
			return (end_point);
	}
	return (end_point - 1);
}

int	expansion_separator(char ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (0);
	else if (ch >= '0' && ch <= '9')
		return (0);
	else if (ch == '_')
		return (0);
	return (1);
}

void	split_after_expansion(t_token *token, char *str, char *new, char *re)
{
	int		idx;
	char	**split;
	t_token	*next;
	t_token	*tmp;

	re[ft_strlen(re)] = 0;
	split = ft_split(str, ' ');
	next = token->next;
	token->next = NULL;
	tmp = token;
	idx = -1;
	while (split[++idx])
	{
		if (idx == 0 && str[0] != ' ')
			ft_strlcat(new, split[0], ft_strlen(new) + ft_strlen(split[0]) + 2);
		else
		{
			connect_remainder(split, idx, re, token);
			make_token(split[idx], ft_strlen(split[idx]), -1, &token);
			tmp = tmp->next;
		}
		free(split[idx]);
	}
	free(split);
	tmp->next = next;
}
