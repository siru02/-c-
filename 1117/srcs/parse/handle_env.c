/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:29:34 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/17 15:09:56 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*insert_envp(t_token *token, char *tmp, char *str, int start)
{ //반환값은 현재토큰의 value로 들어가야하는 새로운 문자열 //token->value는 프리된상태
	char	*new;
	int		new_len;
	int		str_len;

	if (tmp[0] == '\0') //이게 뭐지
		tmp[0] = '\0';
	printf("tmp : %s %d\n",tmp, start); //tmp에는 $~~이후의 문자열이 들어있다 ->$a$b이면 $a확장중에 $b가 tmp에 들어있다
	str_len = ft_strlen(str);
	token->quote_end += str_len;
	new_len = ft_strlen(tmp) + str_len + 1;
	new = malloc(new_len);
	if (new == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(new, tmp, start + 1); //new에 확장이전의 문자열을 붙여넣는다
	if (token->flag == 1) //이 경우임 1117수정중
	{
		printf("inser_envp : %s %s\n", str, new);
		split_after_expansion(token, str, new, tmp); //수정해야함 // $a$b토큰의 경우 token->value에는 $a이전의 문자열인 '\0'만 남게되고 
		printf("inser_envp2 : %s %s\n", str, new);
	}
	else //큰따옴표에서 확장한 경우
	{
		ft_strlcat(new, str, new_len);
		ft_strlcat(new, tmp + start, new_len);
	}
	printf("inser_envp3 : %s\n", new);
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
