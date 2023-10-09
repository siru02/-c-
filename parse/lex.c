/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:01:44 by hgu               #+#    #+#             */
/*   Updated: 2023/10/08 18:02:14 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//main에서 envp인자를 입력받아서 여기까지 이어준다

//이 함수는 env라는 환경변수의 경로를 입력받아 명령어가 저장되어있는 경로만 뽑아내 문자열 배열로 반환한다
// char	**make_env_path(void)
// {//envp는 쉘에 env해서 얻은 결과를 문자열배열로 저장하고있는 main에 입력받는 인자이다 //getenv("PATH")로 경로 입력받을것
// 	char	**env_path;

// 	env_path = ft_split(getenv("PATH"), ':');
// 	return (env_path);
// }

// int main()
// {
// 	char	**env_path;

// 	env_path = ft_split(getenv("PATH"), ':');
// 	while (*env_path)
// 		printf("%s\n", *env_path++);
// }

void	lexer(t_token *token_head)
{
	t_token	*tmp;
	char	**env_path;

	env_path = ft_split(getenv("PATH"), ':');
	tmp = token_head;
	while (tmp != NULL)
	{
		if (tmp->type == D_QUOTATION || tmp->type == S_QUOTATION)
			tmp->type = -1;
		// if (tmp == token_head && tmp->type == -1) //현재 토큰의 타입이 미지정인 상태이면
		// 	tmp->type = COMMAND;
		// if (tmp != token_head && )//현재 토큰이 헤드가 아니면
		// 	// access() -> cmd
		// 	// strlen && strcmp -> builtin(ex. export, exit, )
		// 	// //모든 env경로를 앞에 앞에 붙여서 명령어가 맞는지 체크한다
		// 	// //현재 들어온 문자열이 이미 경로가 붙어서 온 명령어인지 확인해야한다
	}
}
