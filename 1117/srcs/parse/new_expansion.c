/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:51:10 by hgu               #+#    #+#             */
/*   Updated: 2023/11/17 15:29:39 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_token	*delete_empty_token(t_token *head)
{
	t_token	*bef;
	t_token	*now;

	now = head->next;
	bef = head;
	if (head->next == NULL)
		return (free_all_token(head));
	while (now != NULL)
	{
		if (now->value[0] == '\0' && !(bef->type == PIPE || \
		(bef->type >= 7 && bef->type <= 10) \
		|| (!ft_strncmp(bef->value, "cat", 3) && !now->expansion_fail)))
		{
			bef->next = now->next;
			free(now->value);
			if (now->expansion_fail != NULL)
				free(now->expansion_fail);
			free(now);
			now = bef;
		}
		bef = now;
		now = now->next;
	}
	return (head);
}

void	connect_remainder(char **split, int idx, char *remain, t_token *token)
{
	int		len;
	char	*tmp;

	if (split[idx + 1] == NULL) //마지막 스플릿토큰이라면
	{
		printf("split : %s\n",split[idx]);
		printf("new : %s\n",remain);
		len = ft_strlen(split[idx]);
	}
	else
		return ;
	len += ft_strlen(remain) - token->remain_idx;
	tmp = (char *)malloc(len + 1);
	if (tmp == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(tmp, split[idx], len + 1);
	ft_strlcat(tmp, remain + token->remain_idx, len + 2);
	free(split[idx]);
	split[idx] = tmp;
	printf("split : %s\n",split[idx]);
}

void	split_after_expansion(t_token *token, char *str, char *new, char *remain)
{ //remain은 확장뒤에 남은것들 //test$a$b 입력시 new에는 test저장 str에는 확장결과 저장
	int		idx;
	char	**split;
	t_token	*next;
	t_token	*tmp;

	remain[ft_strlen(remain)] = 0; //remain[token->remain_idx]부터 붙여넣기
	split = ft_split(str, ' '); //여기서 자르고 이어붙이는게 잘못된다
	next = token->next; //next에는 현재 토큰의 다음토큰주소를 넣어준다
	token->next = NULL; //현재토큰의 next를 널포인터로 초기화한다
	tmp = token; //tmp에 현재토큰저장
	idx = -1;
	printf("pz : %s %s %s\n",str, new, remain);  //new에는 확장전 앞의 부분이 저장되어 있고,
	//remain에는 확장하는 부분 빼고 다 저장되어 있음
	while (split[++idx])
	{ //확장하면서 각 토큰을 붙여주고 제일 마지막 토큰에 확장한 부분 이후의 문자열을 붙여준다
		if (idx == 0 && str[0] != ' ') //첫 단어가 공백이 아니면 문자열뒤에 이어붙이고
		{
			ft_strlcat(new, split[0], ft_strlen(new) + ft_strlen(split[0]) + 2);
		}
		else //첫 단어가 공백이면 뒤에 이어붙인다
		{
			connect_remainder(split, idx, remain, token); //1117
			make_token(split[idx], ft_strlen(split[idx]), -1, &token); //만약 존재한다면 현재토큰의 뒤에 이어붙인다
			tmp = tmp->next;
		}
		free(split[idx]);
	}
	free(split);
	tmp->next = next;
}

int	new_expand(t_token *token, int start, int cut, t_bundle *bundle)
{
	int	idx;
	int	after_expansion;

	idx = -1;
	if (token->value[start + 1] == '?'
		|| ft_isalpha(token->value[start + 1]) == 0)
		return (dollar_with_separator(token, start));
	while (bundle->envp[++idx] != NULL)
	{
		if (ft_strncmp(token->value + start + 1,
				bundle->envp[idx], cut - start) == 0
			&& bundle->envp[idx][cut - start] == '=')
		{
			after_expansion = case_find_in_envp(token,
					bundle->envp[idx], start, cut);
			return (after_expansion);
		}
	}
	case_not_find_in_envp(token, start, cut);
	return (start - 1);
}

void	set_flag(t_token *token, int idx)
{
	if (idx == token->quote_end + 1)
		token->flag = 1;
	if (token->flag == 1 && token->value[idx] == '\'')
		token->flag = -1;
	else if (token->flag == 1 && token->value[idx] == '\"')
		token->flag = 0;
	else if (token->flag == 0 && token->value[idx] == '\"')
		token->flag = 1;
	else if (token->flag == -1 && token->value[idx] == '\'')
		token->flag = 1;
}

t_token	*expansion_main(t_token *head, t_bundle *bundle)
{
	t_token	*tmp;
	int		idx;

	if (head == NULL)
		return (NULL);
	tmp = head->next;
	while (tmp != NULL)
	{
		idx = -1;
		tmp->flag = 1;
		while (tmp->value[++idx] != '\0')
		{
			printf("main : %s %c %d\n", tmp->value, tmp->value[idx], idx);
			set_flag(tmp, idx);
			idx = check_dollar(tmp, idx, bundle);
			printf("after_check_dollar : %s %d\n", tmp->value, idx); //1회확장후 이전에 남아있는 토큰은 연결을 이렇게 한다
		}
		check_expansion_cnt(tmp);
		tmp = tmp->next;
	}
	return (delete_empty_token(head));
}
