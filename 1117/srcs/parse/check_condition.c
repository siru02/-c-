/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_condition.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:15:57 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/17 15:00:53 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_dollar(t_token *token, int idx, t_bundle *bundle)
{
	char	*str;
	int		cut;

	str = token->value;
	if (token->flag >= 0 && str[idx] == '$')
	{
		if (str[idx + 1] == '\0')
			return (idx);
		cut = cut_env_idx(token, token->value, idx);
		idx = new_expand(token, idx, cut, bundle);
	}
	return (idx);
}

void	check_expansion_cnt(t_token *token)
{
	if (token->expansion_cnt == 0)
		delete_quote(token);
	else
		delete_quote_after_expansion(token);
}

void	case_not_find_in_envp(t_token *token, int start, int cut)
{
	int		len;
	int		malloc_size;
	char	*tmp;

	len = ft_strlen(token->value);
	malloc_size = len - (cut - start + 1) + 1;
	tmp = malloc(malloc_size);
	if (tmp == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(tmp, token->value, start + 1);
	ft_strlcat(tmp, token->value + cut + 1, malloc_size);
	if (token->expansion_fail != NULL)
		free(token->expansion_fail);
	token->expansion_fail = token->value;
	token->value = tmp;
	return ;
}
int	set_len(char *str)
{
	printf("set_len : %s\n",str);
	if (str[0] == ' ') //첫 문자가 공백이면 현재 토큰은 건너뛰고 다음 토큰부터 붙여준다
		return (0);
	return (ft_strlen(str));
}

int	case_find_in_envp(t_token *token, char *envp, int start, int cut)
{ //여기서 탐색해야하는 인자값 반환에 실패 //dsfkljsdlkfksdj반환하는 값은 현재 토큰에서 앞으로 탐색해야하는 인덱스 -1 
	char	*tmp;
	char	*str;
	int		quote_cnt;
	int		len;

	token->expansion_cnt++;
	str = envp + cut - start + 1;
	quote_cnt = 0;
	//len = ft_strlen(str); //이게 문제네
	len = set_len(str); //len은 확장 한 결과값의 길이
	tmp = malloc(ft_strlen(token->value));
	if (tmp == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(tmp, token->value, start + 1);
	token->remain_idx = ft_strlen(tmp); //1117수정
	ft_strlcat(tmp, token->value + cut + 1, ft_strlen(token->value));
	tmp = del_quote(token, tmp, start, &quote_cnt);
	free(token->value); ///////////////////////////////////////////////////////////////////////////////////////
	token->value = insert_envp(token, tmp, str, start - quote_cnt); //현재토큰의 value값을 여기서 설정하는데 a="  aa"의 경우 토큰엔 원래 토큰의 앞의 값들만 남아있고 aa는 토큰 뒤에 이어붙인다
	printf("case : %d %d %d %d\n", start, len, quote_cnt, start + len - 1 - quote_cnt);
	return (start + len - 1 - quote_cnt);
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
