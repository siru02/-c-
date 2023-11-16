/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:29:34 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/16 15:28:34 by hgu              ###   ########.fr       */
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
	{
		printf("inser_envp : %s %s %s\n", token->value, str, new);
		split_after_expansion(token, str, new);
	}
	else
		ft_strlcat(new, str, new_len);
	ft_strlcat(new, tmp + start, new_len);
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
