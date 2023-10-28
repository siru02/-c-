/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:35:42 by hgu               #+#    #+#             */
/*   Updated: 2023/10/28 21:50:43 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int expansion_separator(char ch)
{ //소문자 대문자 숫자 언더바 제외하고는 확장구분자로 사용된다 //$바로뒤에 숫자가 오면 그 숫자랑 $를 같이 지워버린다
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) //대소문자이면
	 	return (0); //구분자가 아니다
	else if (ch >= '0' && ch <= '9') //숫자이면
		return (0);
	else if (ch == '_')//언더바이면	
		return (0);
	return (1); //구분자이다
}

int	cut_env_idx(char *value, int idx)
{ //문자열과 $로 시작하는 시작주소를 받아서 확장해야할 단어의 마지막문자열 주소인덱스를 반환한다 //$abc 이면 $의 주소idx를 받고, c의 주소 idx를 반환하도록 한다
	int	end_point;

	end_point = idx;
	while (value[++end_point]) // \0에서 반복문 종료
	{
		if (expansion_separator(value[end_point])) //1을 리턴하면 구분자인경우다
			break ;
	}
	return (end_point);
}

void	expand(t_token *token, int start, int end, t_bundle *bundle)
{
	int		idx; //envp 문자열 배열 탐색에 사용하는 변수
	char	*tmp; //임시 말록할 변수
	char	*str; //envp에서 $이후의 시작주소를 저장할 변수
	int		len; //변환결과의 길이

	idx = -1;
	while (bundle->envp[++idx]) //문자열배열의 마지막원소는 NULL이므로
	{
		if (strncmp(token->value + start, bundle->envp[idx], end - start) == 0) //일치하는 경우
		{//일치하는 경우의 처리
			str = bundle->envp[idx] + end - start + 1;//확장해야할 값의 단어의 시작주소로 이동 //$abc -> 0 3 // abc=kkk
			len = ft_strlen(str); //변환결과물의 길이
			tmp = malloc(ft_strlen(token->value) + len - (end - start + 1) + 1); //원래길이 + 결과물길이 - 원래$~의 길이 + 1
			ft_strlcpy(tmp, token->value, start - 1);//수정필요
			ft_strlcat(tmp, str, len);//수정필요
			ft_strlcat(tmp, token->value + end, ft_strlen(token->value + end));//수정필요
			return ;
		}
	} //$숫자 조합의 경우 일치하는 경우를 찾지 못한다 -> 원래 $숫자는 제거해야하므로 제거하는 연산을 수행한다
	tmp = malloc(ft_strlen(token->value) - 1);
	ft_strlcpy(tmp, token->value, start - 1);
	ft_strlcat(tmp, token->value + end, ft_strlen(token->value + end));
	return ;
}

//export는 숫자로 시작하면 안된다
void	expansion(t_token *head, t_bundle *bundle)
{//따옴표는 나중에 땐다
	t_token *tmp;
	int		idx;
	int		cut;
	int		flag; //flag == 1이면 큰따옴표나 따옴표밖에 있는 상태 -> 확장가능, flag == -1이면 작은 따옴표 안인 상태 -> 확장불가능

	tmp = head;
	flag = 1;
	while (tmp != NULL) //토큰을 마지막까지 탐색한다
	{
		idx = -1;
		while (tmp->value[++idx] != '\0') //문자열을 탐색한다
		{
			if (tmp->value[idx] == '\'') //작은 따옴표는 $로 확장이 불가능하므로 flag를 따로 준다
				flag *= -1;
			if (flag == 1 && tmp->value[idx] == '$') //$를 만나면
			{
				cut = cut_env_idx(tmp->value, idx); //환경변수 마지막 문자의 주소를 반환하도록 한다
				if (tmp->value[idx + 1] >= '0' && tmp->value[idx + 1] <= '9')
					cut = idx + 1;
				expand(tmp, ++idx, cut, bundle); //idx는 $바로 다음주소, cut은 $~~의 마지막주소
				idx = cut;
			}
		}
		delete_quote(tmp);
	}
}
//envp -> hi=123
// echo $hi abc -> echo 123 abc
// echo "$hi" -> echo "123"
// echo "$hi"c -> echo "123"c -> echo 123c