/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:35:43 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/17 15:32:17 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

t_token	*traverse_str(char *str, t_token *token_head, int *len, int *type)
{
	while (*(str + (++(*len))))
	{
		*type = check_ch_is_token(str + *len);
		if (*type == S_QUOTATION || *type == D_QUOTATION)
			*len = jump_quote(str, *len);
		if (*len == -1)
		{
			write(STDERR_FILENO, "quote error\n", 12);
			return (free_all_token(token_head));
		}
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
