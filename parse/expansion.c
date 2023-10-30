/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:35:42 by hgu               #+#    #+#             */
/*   Updated: 2023/10/30 22:07:23 by hgu              ###   ########.fr       */
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
		if (expansion_separator(value[end_point])) //1을 리턴하면 구분자인경우다 //구분자란 (_, 숫자, 영문자)                                                                                                                                       를 제외한 모든 문자
			break ;
	}
	return (end_point);
}

char	*dollar_with_num(char *value, int start, int end)
{
	char	*tmp;

	tmp = malloc(ft_strlen(value) - 1); //$와 숫자를 제외하고 나머지를 워드로 취급한다
	ft_strlcpy(tmp, value, start - 1);
	ft_strlcat(tmp, value + end, ft_strlen(value + end));
	free(value);
	return (tmp);
}
void	find_in_envp(t_token *token, char *envp, int start, int cut)
{ //envp명단에서 일치하는 확장명령어를 발견했으면
	char	*str;
	char	*tmp;
	int		len;
	int		malloc_size;
	
	str = envp + cut - start + 1;//확장해야할 값의 단어의 시작주소로 이동 //$abc -> 0 3 // abc=kkk
	len = ft_strlen(str); //변환결과물의 길이
	malloc_size = ft_strlen(token->value) + len - (cut - start + 1) + 1;
	tmp = malloc(malloc_size); //원래길이 + 결과물길이 - 원래$~의 길이 + 1만큼 말록한다
	ft_strlcpy(tmp, token->value, start - 1);//수정필요 //$나오기 직전까지 원래 문자열을 복사한다
	ft_strlcat(tmp, str, malloc_size);//수정필요 //tmp뒤에 str을 붙여준다
	ft_strlcat(tmp, token->value + cut + 1, malloc_size);//수정필요 //tmp뒤에 원래 $~~ 뒤에 있던 부분을 붙여준다
	free(token->value);
	token->value = tmp;
	return ;
}

void	not_find_in_envp(t_token *token, int start, int cut)
{//찾지 못했으면 토큰에서 $~~~부분을 지운다
	int		len;
	int		malloc_size;
	char	*tmp;

	len = ft_strlen(token->value);
	malloc_size = len - (cut - start + 1) + 1;//원래길이 - $~~길이 + 1(NULL) //$abc=123 // start =0, cut = 3
	tmp = malloc(malloc_size);
	ft_strlcpy(tmp, token->value, start - 1);//수정필요 //$나오기 직전까지 원래 문자열을 복사한다
	ft_strlcat(tmp, token->value + cut + 1, malloc_size);//수정필요 //tmp뒤에 원래 $~~ 뒤에 있던 부분을 붙여준다
	free(token->value);
	token->value = tmp;
	return ;
}

void	expand(t_token *token, int start, int cut, t_bundle *bundle) //여기서 터진다 //envp가 아직 없으니까 터지는게 당연하다
{ //start는 $의 인덱스 : token->value[idx] == '$', cut은 $로부터 이어지는 마지막인덱스
	int		idx; //envp 문자열 배열 탐색에 사용하는 변수
	char	*tmp; //임시 말록할 변수

	idx = -1;
	if (token->value[idx + 1] >= '0' && token->value[idx + 1] <= '9') //$바로 뒤 문자가 숫자이면 $숫자 를 제거하고 나머지만 남긴다
	{
		tmp = dollar_with_num(token->value, start, cut);
		token->value = tmp;
		return ;
	}
	while (bundle->envp[++idx] != NULL) //문자열배열의 마지막원소는 NULL이므로 순회
	{
		if (strncmp(token->value + start, bundle->envp[idx], cut - start) == 0) //envp의 명단중 하나와 일치하는 경우
		{//일치하는 경우엔 $hi@@같은 경우이면 현재 토큰이 $hi와 @@로 나뉜다, 만악 $hi가 존재하지 않으면 token을 삭제한다
			printf("find envp\n");
			find_in_envp(token, bundle->envp[idx], start, cut);
			return ;
		}
	}// 찾지 못했으면 $~~를 삭제한다
	not_find_in_envp(token, start, cut);
}
int	check_dollar(t_token *tmp, int idx, int flag, t_bundle *bundle)
{
	int	cut;

	if (flag == 1 && tmp->value[idx] == '$') //''내부가 아니고 $를 만나면 //idx는 $를 가리키는 상태
	{
		cut = cut_env_idx(tmp->value, idx); //환경변수 마지막 문자의 주소를 반환하도록 한다
		expand(tmp, idx, cut, bundle); //idx는 $를 가리키고, cut은 $~~의 마지막주소
		return (cut); //cut을 반환
	}
	return (idx); //들어온 idx그대로 반환
}


//export는 숫자로 시작하면 안된다
void	expansion(t_token *head, t_bundle *bundle)
{//따옴표는 나중에 땐다
	t_token *tmp;
	int		idx;
	int		flag; //flag == 1이면 큰따옴표나 따옴표밖에 있는 상태 -> 확장가능, flag == -1이면 작은 따옴표 안인 상태 -> 확장불가능

	tmp = head->next; //token의 head는 빈문자를 가지고 있음
	flag = 1;
	while (tmp != NULL) //토큰을 마지막까지 탐색한다
	{
		idx = -1;
		printf("before expansion token : %s\n",tmp->value);
		while (tmp->value[++idx] != '\0') //토큰의 value 문자열을 탐색한다
		{
			if (tmp->value[idx] == '\'') //작은 따옴표는 $로 확장이 불가능하므로 flag를 따로 준다
				flag *= -1;
			idx = check_dollar(tmp, idx, flag, bundle); //check_dollar함수는 tmp->value[idx] == '$'이면 확장을 수행하고 마지막 지점의 idx반환
		}
		//delete_quote(tmp); //한토큰의 탐색이 끝나면 따옴표를 제거해준다
		printf("after expansion token : %s\n",tmp->value);
		tmp = tmp->next; //만약 현재 token에서 $를 발견하면 확장 -> 
	}
}
//envp -> hi=123
// echo $hi abc -> echo 123 abc
// echo "$hi" -> echo "123"
// echo "$hi"c -> echo "123"c -> echo 123c