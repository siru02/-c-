/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:21:02 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/15 15:25:08 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	dollar_with_separator(t_token *token, int idx)
{
	char	*tmp;
	int		len;

	if (token->value[idx + 1] == '\'' || token->value[idx + 1] == '\"')
		return (dollar_with_quote(token, idx + 1));
	else if (token->value[idx + 1] == '$')
		return (dollar_with_dollar(token, idx));
	else if (token->value[idx + 1] == '?')
		return (dollar_with_question_mark(token, idx));
	len = ft_strlen(token->value);
	tmp = malloc(len);
	if (tmp == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(tmp, token->value, idx + 1);
	ft_strlcat(tmp, token->value + idx + 1, len);
	free(token->value);
	token->value = tmp;
	return (idx - 1);
}

int	dollar_with_question_mark(t_token *token, int idx)
{
	char	*exit_code;
	char	*tmp;
	int		len;
	int		malloc_size;

	exit_code = ft_itoa(g_exit_status);
	len = ft_strlen(exit_code);
	malloc_size = ft_strlen(token->value) - 2 + len + 1;
	tmp = malloc(malloc_size);
	if (tmp == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(tmp, token->value, idx + 1);
	ft_strlcat(tmp, exit_code, ft_strlen(tmp) + len + 1);
	ft_strlcat(tmp, token->value + idx + 2, malloc_size);
	free(token->value);
	free(exit_code);
	token->value = tmp;
	return (idx + len - 1);
}

int	dollar_with_dollar(t_token *token, int idx)
{
	char	*pid;
	char	*tmp;
	int		len;
	int		malloc_size;

	pid = ft_itoa(getpid());
	len = ft_strlen(pid);
	malloc_size = ft_strlen(token->value) - 2 + len + 1;
	tmp = malloc(malloc_size);
	if (tmp == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(tmp, token->value, idx + 1);
	ft_strlcat(tmp, pid, ft_strlen(tmp) + len + 1);
	ft_strlcat(tmp, token->value + idx + 2, malloc_size);
	free(token->value);
	free(pid);
	token->value = tmp;
	return (idx + len - 1);
}

void	find_close_quote_with_dollar(t_token *token, int *close_quote)
{
	int	idx;

	idx = *close_quote;
	while (token->value[++idx])
	{
		if (token->value[idx] == token->value[*close_quote])
		{
			token->value = new_cut_quote(*close_quote, idx, token->value);
			token->quote_end = idx - 2;
			if (idx < *close_quote)
				*close_quote -= 1;
			token->value = delete_only_dollar(token->value, *close_quote - 1);
			break ;
		}
	}
}

char	*delete_only_dollar(char *value, int dollar)
{
	char	*str;
	int		len;

	len = ft_strlen(value);
	str = malloc(len);
	if (str == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(str, value, dollar + 1);
	ft_strlcat(str, value + dollar + 1, len);
	free(value);
	return (str);
}
