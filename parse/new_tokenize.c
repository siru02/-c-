/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:51:20 by hgu               #+#    #+#             */
/*   Updated: 2023/10/09 21:58:49 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_ch_is_token(char *str)
{
	if (*str == ' ' || *str == 9 || *str == 10 || *str == 11 || *str == 12 || *str == 13) //현재문자가 공백이면
		return (WHITE_SPACE); //white_space 
	else if (*str == '>') //리다이렉션 > 기호이면 다음 기호까지 확인한다
	{
		if (*(str + 1) == '>') //>>이면
			return (REDIR_TWO_RIGHT);
		return (REDIR_RIGHT); //>>이 아니면
	}
	else if (*str == '<')
	{
		if (*(str + 1) == '<')
			return (REDIR_TWO_LEFT);
		return (REDIR_LEFT);
	}
	else if (*str == '\'') //작은 따옴표
		return (S_QUOTATION);
	else if (*str == '\"') //큰 따옴표
		return (D_QUOTATION);
	else if (*str =='|') //PIPE
		return (PIPE);
	else if (*str == '\0') //문자마지막이면
		return (100);
	return (-1); //word
}

int	set_flag(char *str)
{
	if (*str == '\'')
		return (S_QUOTATION);
	else if (*str == '\"')
		return (D_QUOTATION);
	return (-1);
}

void	make_new_token(char *str, int len, int type, t_token **head)
{
	t_token	*new;
	int		idx;

	idx = -1;
	new = malloc(sizeof(t_token));
	new->next = NULL;
	new->type = type;
	new->value = malloc(sizeof(len + 2));
	if (*head == NULL)
		*head = new;
	else
	{
		while ((*head)->next != NULL)
			*head = (*head)->next;
	}
	while (++idx < len)
		new->value[idx] = str[idx];
	new->value[idx] = '\0';
}
//토큰은 현재 타입이 문자 && 다음 타입이 구분자 or 현재타입이 구분자인경우
//구분자는 스페이스, 파이프, 리다이렉션의 3가지만 구분한다
//따옴표안에 있으면 스킵한다
t_token	*tokenize(char *str)
{
	int		type; //각  token의 type값으로 -1이면 덩어리 멤버
	int		len; //각 token의 문자 길이
	t_token	*token_head;
	int		flag; //0은 따옴표밖, 1은 작은따옴표안, 2은 큰 따옴표안 임을 의미한다

	len = -1;
	token_head = NULL;
	while (*str + ++len)
	{	//*(str + len)이 현재 읽고있는 단어
		while (check_ch_is_token(str + len) == SPACE) //현재 타입이 공백인동안 str계속 증가
			str++;
		type = check_ch_is_token(str + len);
		flag = set_flag(str + len); //따옴표인지 아닌지 확인
		while (flag == D_QUOTATION || flag == S_QUOTATION) //따옴표이면
		{
			if (check_ch_is_token(str + ++len) == flag) //따옴표가 닫힐때까지 len을 증가시킨다
				flag = -1;
		}
		if (check_ch_is_token(str + len) == -1 && check_ch_is_token(str + len + 1) >= 3)
		{
			make_new_token(str, len, type, &token_head);
			str = str + len + 1;
			len = -1;
		}
	}
	make_new_token(str, len - 1, type, &token_head);
	return (token_head);
}

int main()
{
	t_token	*head;
	t_token	*tmp;
	t_token *to_free;
	char	*ret;

	//atexit(check_leak);
	while (1)
	{
		ret = readline("hgu hi : ");
		head = tokenize(ret);
		tmp = head;
		if (head == NULL)
			printf("successfully freed\n");
		// else
		// 	tmp = syntax_analyze(head);
		printf("여기까지 동작\n");
		while (tmp != NULL)
		{
			printf("type : %d len : %zu new : %s\n",tmp->type,ft_strlen(tmp->value), tmp->value);
			to_free = tmp;
			tmp = tmp->next;
			free(to_free->value);
			free(to_free);
		}
		free(ret);
		// return(0);
	}
}
