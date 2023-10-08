/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   systac_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:50:39 by hgu               #+#    #+#             */
/*   Updated: 2023/10/08 18:02:11 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	syntax_error(char *str)  //출력할 오류문구를 입력받아 출력하고, -1리턴
{
	write(2, "bash: syntax error near unexpected token", 40);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (-1);
}

//각 파이프마다 첫 토큰은 명령어나 리다이렉션만 올 수 있으므로, word인 경우 command로 타입을 변경해줌
int	syntax_first_token(t_token *first)
{
	if (first->type >= REDIR_LEFT && first->type <= REDIR_TWO_RIGHT) //첫 커맨드가 리다이렉션이면 정상적인 경우이다
		return (1);
	else if (first->type == -1) //word는 cmd, filename, option으로 분류되는데 첫커맨드가 리다이렉션이 아니면 항상 cmd로 인식한다
		first->type = COMMAND;
	else if (first->type == PIPE) //파이프뒤에 바로 파이프가 나오면
	{
		if (first->next && first->next->type == PIPE) //파이프가 연속으로 2개 붙어있으면
			return (syntax_error(" `||\'"));
		return (syntax_error(" `|'"));
	}
}
int	syntax_redirection(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type >= REDIR_LEFT && tmp->type <= REDIR_TWO_RIGHT)
}

//앞의 토큰과 대조해서 현재토큰에 타입을 지정해준다
// 파이프바로뒤의 토큰은 '리다이렉션' or '커맨드' 이다
// 리다이렉션 바로뒤의 토큰은 filename만 온다
// cmd뒤의 토큰들은 파이프나 리다이렉션이 오기 전까지 word로 취급하며, argv에 문자열배열로 들어간다
// 명령어뒤의 부적절한 리다이렉션은 오류를 newline으로 뱉어낸다
// 여기서 모든 문법적 오류들을 처리한다
// 오류가 있으면 NULL리턴, 문법오류없으면 head의 주소리턴
t_token	*systax_analyze(t_token *token_head)
{
	t_token	*tmp;

	tmp = token_head;
	while (tmp != NULL)
	{
		if (systax_first_token(tmp) == -1)//매 파이프마다 첫 토큰은 리다이렉션과 명령어만 올 수 있다
			return (free_all_token(token_head));
		while(tmp->type != PIPE) //현재 토큰의 타입이 파이프가 아닌동안 의미를 부여한다
		{
			syntax_redirection(tmp); //tmp의 type이 redirection인 경우 문법검사를 수행한다
		}
	}
}
