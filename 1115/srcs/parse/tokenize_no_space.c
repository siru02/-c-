/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_no_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 16:18:40 by hgu               #+#    #+#             */
/*   Updated: 2023/11/14 23:12:56 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_token	*free_all_token(t_token *token_head)
{
	t_token	*tmp;
	t_token	*to_free;

	tmp = token_head;
	while (tmp != NULL)
	{
		to_free = tmp;
		tmp = tmp->next;
		free(to_free->value);
		free(to_free);
	}
	return (NULL);
}

void	set_new_token(t_token *new, int type)
{
	new->next = NULL;
	new->type = type;
	new->expansion_cnt = 0;
	new->quote_end = -1;
	new->quote_start = -1;
	new->expansion_fail = NULL;
}

void	make_token(char *str, int len, int type, t_token **head)
{
	t_token	*new;
	t_token	*tmp;
	int		idx;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	set_new_token(new, type);
	if (*head == NULL)
	{
		*head = new;
		(*head)->value = NULL;
		return ;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->value = malloc(sizeof(char) * (len + 2));
	if (new->value == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	idx = -1;
	ft_strlcpy(new->value, str, len + 2);
}

int	check_ch_is_token(char *str)
{
	if (*str == ' ' || *str == 9 || \
	*str == 10 || *str == 11 || *str == 12 || *str == 13)
		return (WHITE_SPACE);
	else if (*str == '>')
	{
		if (*(str + 1) == '>')
			return (REDIR_TWO_RIGHT);
		return (REDIR_RIGHT);
	}
	else if (*str == '<')
	{
		if (*(str + 1) == '<')
			return (REDIR_TWO_LEFT);
		return (REDIR_LEFT);
	}
	else if (*str == '\'')
		return (S_QUOTATION);
	else if (*str == '\"')
		return (D_QUOTATION);
	else if (*str == '|')
		return (PIPE);
	else if (*str == '\0')
		return (100);
	return (-1);
}

int	jump_quote(char *s, int idx)
{
	if (s[idx] == '\'')
	{
		while (s[idx + 1] && s[idx + 1] != '\'')
			idx++;
		if (s[idx + 1] == '\0')
			write(2, "error1\n", 7);
	}
	else if (s[idx] == '\"')
	{
		while (s[idx + 1] && s[idx + 1] != '\"')
			idx++;
		if (s[idx + 1] == '\0')
			write(2, "error2\n", 7);
	}
	if (s[idx + 1] == '\0')
		return (-1);
	return (idx + 1);
}

t_token	*traverse_str(char *str, t_token *token_head, int *len, int *type)
{
	while (*(str + (++(*len))))
	{
		*type = check_ch_is_token(str + *len);
		if (*type == S_QUOTATION || *type == D_QUOTATION)
			*len = jump_quote(str, *len);
		if (*len == -1)
			return (free_all_token(token_head));
		if (*type == WHITE_SPACE)
		{
			str++;
			(*len)--;
		}
		if ((*type <= 1 && check_ch_is_token(str + *len + 1) > 1) || *type > 3)
		{
			if (*type == REDIR_TWO_LEFT || *type == REDIR_TWO_RIGHT)
				(*len)++;
			make_token(str, *len, *type, &token_head);
			str = str + *len + 1;
			*len = -1;
		}
	}
	return (token_head);
}


t_token	*tokenize(char *str)
{
	int		type;
	int		len;
	t_token	*token_head;

	len = -1;
	token_head = NULL;
	make_token(NULL, 0, PIPE, &token_head);
	if (traverse_str(str, token_head, &len, &type) == NULL)
		return (NULL);
	if (type != WHITE_SPACE && len != 0)
		make_token(str, --len, type, &token_head);
	return (token_head);
}
