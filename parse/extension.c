/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:35:42 by hgu               #+#    #+#             */
/*   Updated: 2023/10/13 23:19:56 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	handle_env_in_string(t_token *token, int idx)
{
	int	tmp;

	tmp = idx;
	while (token->value[tmp++] != NULL && token->value[tmp++] != quote && token->value[tmp++] != space)
	//환경변수이름의 자르는 부분을 정하는 기준 : 따옴표오면 컷, 공백나오면 컷, NULL나오면 컷, 
	//**숫자 문자 언더바 아닐 때 까지 환경변수 이름으로 생각**
}

void	renewal_token(t_token *token, int idx, int quote)
{
	int	tmp;

	tmp = idx;
	if (quote == S_QUOTATION)
	{
		while (token->value[++tmp])
		{
			if (token->value[tmp] == '$') //확장해야한다
				handle_env_in_string(token, tmp); //현재토큰과 $위치인덱스를 인자로 넘겨준다
		}
	}
}

void	check_quote(t_token *token) //따옴표 찾고 있으면 제거하는 함수
{
	int	idx;

	idx = -1;
	while (token->value[++idx])
	{
		if (token->value[idx] == S_QUOTATION) //작은 따옴표이면
			renewal_token(token, idx, S_QUOTATION); 
		else if (token->value[idx] == D_QUOTATION) //큰 따옴표이면
			renewal_token(token, idx, D_QUOTATION);
	}
}

void	extension(t_token *head) //확장 + 따옴표제거의 메인함수?
{
	t_token	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (tmp->type == -1) //word이면
			check_quote(tmp); //따옴표 있으면 제거하는 함수로 들어감
	}
}