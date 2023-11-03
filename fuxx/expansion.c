/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:35:42 by hgu               #+#    #+#             */
/*   Updated: 2023/11/03 23:50:12 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	delete_empty_token(t_token *head)
{//토큰의 헤드는 빈문자열을 들고있다
	t_token	*before;
	t_token	*now;

	now = head->next;
	before = head;
	while (now != NULL)
	{
		if (now->value[0] == '\0')//토큰이 빈 문자열이면
		{
			before->next = now->next; //이전노드의 next를 현재노드의 next로 이어준다
			free(now->value); //문자열 free
			free(now); //토큰 free
			now = before;
		}
		before = now;
		now = now->next;
	}
}

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
	int	end_point;//echo $USER의 경우 cut이 5가된다

	end_point = idx;
	while (value[++end_point]) // \0에서 반복문 종료
	{
		if (expansion_separator(value[end_point])) //1을 리턴하면 구분자인경우다 //구분자란 (_, 숫자, 영문자)                                                                                                                                       를 제외한 모든 문자
			break ;
	}
	return (end_point - 1);
}

char	*dollar_with_num(char *value, int start, int end)
{
	char	*tmp;

	tmp = malloc(ft_strlen(value) - 1); //$와 숫자를 제외하고 나머지를 워드로 취급한다
	ft_strlcpy(tmp, value, start + 1); //$직전까지 copy한다
	ft_strlcat(tmp, value + end + 1, ft_strlen(value + end)); //end이후의 값을 붙여넣는다
	free(value);
	return (tmp);
}

char	*new_cut_quote(int open, int close, char *target)
{
	char	*str;
	int		malloc_size;

	malloc_size = ft_strlen(target) - 1; //따옴표 2개를 제거하므로 원래길이에서 1개 감소한다('\0'있으므로)
	str = malloc(ft_strlen(target) - 1);
	ft_strlcpy(str, target, open + 1); //quote전까지 복사한다
	printf("cut_quote test1 : %s close : %d open : %d\n",str,close, open);
	ft_strlcat(str, target + open + 1, ft_strlen(str) + close - open); //문제발생
	printf("cut_quote test2 : %s\n",str); //
	ft_strlcat(str, target + close + 1, malloc_size);
	printf("cut_quote test3 : %s\n",str);
	free(target);
	return (str);
}

char	*del_quote(char *target, int start, int *quote_cnt)
{
	int		idx;
	char	ch; //만난 따옴표의 종류를 저장한다 작은 따옴표면 작은따옴표로, -> 닫히는 따옴표를 만나면 널문자로 초기화
	int		open_quote; //시작하는 quote의 인덱스

	*quote_cnt = 0;
	idx = -1;
	ch = '\0';
	while (target[++idx] != '\0')
	{
		if (ch == '\0' && (target[idx] == '\'' || target[idx] == '\"'))
		{
			ch = target[idx];
			open_quote = idx;
			if (idx < start)
			{
				printf("test1 : %c\n",target[idx]);
				(*quote_cnt) += 1;
			}
		}
		else if (ch != '\0' && target[idx] == ch)
		{
			ch = '\0';
			target = new_cut_quote(open_quote, idx, target);
			if (idx < start)
			{
				printf("test2 : %c\n",target[idx]);
				(*quote_cnt) += 1;
			}
			idx = idx - 2; //단어가 2개 줄어들기 때문에 "test"'hi"같은 경우 test파트의 open = 0 close = 5가 된다
		}
	}
	printf("after del quote -> copy : %s \n", target);
	return (target);
} //hi"$test"##  -> hi""##

// void	ft_copy(char *target, char *value, int cut)
// {
// 	char	*tmp;//$~~이후의 문자열을 임시로 저장할 문자열
// 	int		tmp_len; //$~~이후의 문자열의 길이를 저장할 변수

// 	tmp_len = ft_strlen(value + cut + 1);
// 	tmp = malloc(tmp_len + 1);
// 	ft_strlcpy(tmp, value + cut + 1, tmp_len + 1); //tmp에는 $~~이후의 문자열이 담겨있다
// 	printf ("target test : %s\ntmp test : %s\n",target, tmp);
// 	ft_strlcat(target, tmp, ft_strlen(target) + tmp_len + 1); //target에 두 부분을 붙여준다
// 	free(tmp);
// 	printf("testtest : %s\n",target);//target에 제대로 안들어옴
// 	del_quote(target);
// }
/* 
envp[0] test=hgu
envp[1] user=hy'uim

echo test"'$user'"test // echo "$test"
str = hy'uim
tmp = testhy'uimtest 목표
tmp = test"
tmp = test""test
tmp = test^test //^부분주소를 가지고있음
tmp = testhy'uimtest
*/

char	*ft_insert_envp(char *target, char *str, int start)
{//hi"$test"## -> hi##, hyuim, 2
	char	*tmp;
	char	*new_target;
	int		tmp_len;
	int		len;

	printf("start : %d\n", start);
	tmp_len = ft_strlen(target + start); //2
	tmp = malloc(tmp_len + 1);
	ft_strlcpy(tmp, target + start, tmp_len + 1); //tmp에 뒷부분 말록 //여기까지 동작하는듯
	target[start] = '\0';
	printf("target : %s tmp : %s str : %s\n",target, tmp, str);//여기까지 동작하는듯
	len = ft_strlen(target) + ft_strlen(str) + ft_strlen(tmp) + 1;
	new_target = malloc(len);
	printf("len : %d\n", len);
	ft_strlcpy(new_target, target, ft_strlen(target) + 1);
	ft_strlcat(new_target, str, len);
	ft_strlcat(new_target, tmp, len);
	free(tmp);
	free(target);
	return (new_target);
}

int	find_in_envp(t_token *token, char *envp, int start, int cut)
{ //envp명단에서 일치하는 확장명령어를 발견했으면 //start는 $의 인덱스, cut은 마지막 문자의 인덱스 //확장한 안에서 
	char	*str; //abc=kkk에서 kkk의 시작주소 
	char	*target; //확장 완료한 문자들을 저장할 문자열
	int		len;
	int		malloc_size;
	//start는 확장한 단어의 첫 주소, cut은 확장전 마지막 문자의 인덱스
	str = envp + cut - start + 1;//확장해야할 값의 단어의 시작주소로 이동 //$abc -> 0 3 // abc=kkk
	len = ft_strlen(str); //확장변환결과물의 길이
	malloc_size = ft_strlen(token->value) + len - (cut - start + 1) + 1;
	target = malloc(malloc_size); //원래길이 + 결과물길이 - 원래$~의 길이 + 1만큼 말록한다
	ft_strlcpy(target, token->value, start + 1);//수정필요 //$나오기 직전까지 원래 문자열을 복사한다
	printf("target : %s\n", target);
	ft_strlcat(target, token->value + cut + 1, malloc_size); //tmp뒤에 확장할부분을 제외하고 나머지를 복사해준다
	//ft_copy(target, token->value, cut); //target에 $~~를 제외한 부분만 남겨둔다
	printf("copy : %s start : %d cut : %d\n", target, start, cut);
	target = del_quote(target, start, &malloc_size); //start보다 작은 지점에서 quote를 발견하여 지우는경우 //malloc_size가 quote_cnt역할도 한다
	printf("quote_cnt : %d\n",malloc_size); //여기까지 완료
	//여기서 delete_quote실행 //delete_quote에 인자로 원래 token->value의 start를 보낸다 //delete_quote의 반환값으로 줄어든 start
	//tmp에는 현재 quote가 삭제되어있다 start이후의 부분을 맨뒤로 보내주는 함수를 만들어 실행시킨다, target[start] = '\0'해준다
	//tmp의 사이에 str의 값을 넣어주는 함수를 만들어 실행시킨다 
	target = ft_insert_envp(target, str, start - malloc_size); //target = hi""## len = 
	//ft_strlcat(target, token->value + cut + 1, malloc_size);//수정필요 //target뒤에 원래 $~~ 뒤에 있던 부분을 붙여준다
	free(token->value);
	token->value = target;
	//cut - start = 자르기전 문자열의 길이 // hi=test, echo say$hi# start = 3 cut = 5 len = 4 //saytest#
	return (start + len - 1); //확장에 성공했으면 token->value를 수정하고, 다음에 탐색해야할 인덱스 - 1을 반환한다 //위를 수정하면 반환값도 수정해야한다
}

void	not_find_in_envp(t_token *token, int start, int cut)
{//찾지 못했으면 토큰에서 $~~~부분을 지운다
	int		len;
	int		malloc_size;
	char	*tmp;

	len = ft_strlen(token->value);
	malloc_size = len - (cut - start + 1) + 1;//원래길이 - $~~길이 + 1(NULL) //$abc=123 // start =0, cut = 3
	tmp = malloc(malloc_size);
	ft_strlcpy(tmp, token->value, start + 1);//수정필요 //$나오기 직전까지 원래 문자열을 복사한다
	ft_strlcat(tmp, token->value + cut + 1, malloc_size);//수정필요 //tmp뒤에 원래 $~~ 뒤에 있던 부분을 붙여준다
	free(token->value);
	token->value = tmp;
	return ;
}

int	expand(t_token *token, int start, int cut, t_bundle *bundle)
{ //start는 $의 인덱스 : token->value[idx] == '$', cut은 $로부터 이어지는 마지막인덱스 //확장을 하면서 동시에 ""를 제거한다
	int		idx; //envp 문자열 배열 탐색에 사용하는 변수
	char	*tmp; //임시 말록할 변수
	int		after_expantion; //확장한 후 단어의 길이

	idx = -1;
	if (token->value[start + 1] == '?' || ft_isalpha(token->value[start + 1]) == 0) //$?이거나 $뒤가 알파벳이 아니면
	{
		tmp = dollar_with_num(token->value, start, start + 1);
		token->value = tmp;
		return (start - 1); //확장을 실패하는 경우이므로 $의 직전인덱스를 반환해야 밖에서 ++하면서 정상적으로 검사한다
	}
	while (bundle->envp[++idx] != NULL) //문자열배열의 마지막원소는 NULL이므로 순회
	{
		printf("envp : %s start : %d cut : %d\n", bundle->envp[idx], start, cut); //05 $hi=user
		if (strncmp(token->value + start + 1, bundle->envp[idx], cut - start) == 0 && bundle->envp[idx][cut - start] == '=') //envp의 명단중 하나와 일치하는 경우
		{//일치하는 경우엔 $hi@@같은 경우이면 현재 토큰이 $hi와 @@로 나뉜다, 만악 $hi가 존재하지 않으면 token을 삭제한다
			printf("find envp\n");
			after_expantion = find_in_envp(token, bundle->envp[idx], start, cut); //start는 $의 인덱스, cut은 마지막 문자의 인덱스
			return (after_expantion); //확장 성공하는경우
		}
	}// 찾지 못했으면 $~~를 삭제한다
	not_find_in_envp(token, start, cut); //$~~부분을 삭제한다 //오류발생 hi$USER
	return (start - 1);//확장할일이 없는경우
}

int	check_dollar(t_token *tmp, int idx, int flag, t_bundle *bundle)
{ //idx는 현재 인덱스 //hi$tt
	int	cut;
	int	num;

	if (flag == 1 && tmp->value[idx] == '$') //''내부가 아니고 $를 만나면 //idx는 $를 가리키는 상태
	{
		if (tmp->value[idx + 1] == '\0')//$하나만 있으면
			return (idx); //확장하지않는다
		cut = cut_env_idx(tmp->value, idx); //환경변수 마지막 문자의 주소를 반환하도록 한다
		num = expand(tmp, idx, cut, bundle); //idx는 $를 가리키고, cut은 $~~의 마지막주소 //오류발생
		return (num); //확장성공시에는 확장된 마지막 문자열을 반환해야하고, 확장실패시에는 현재 인덱스를 그대로 반환해야한다
	}
	return (idx); //확장하는 경우가 아니면 들어온 idx그대로 반환
}

//export는 숫자로 시작하면 안된다 //$다음문자가 알파벳, ? 아니면 바로 다음거랑 묶어서 날려버린다
void	expansion(t_token *head, t_bundle *bundle)
{//따옴표는 나중에 땐다
	t_token *tmp;
	int		idx;
	int		flag; //flag == 1이면 큰따옴표나 따옴표밖에 있는 상태 -> 확장가능, flag == -1이면 작은 따옴표 안인 상태 -> 확장불가능

	if (head == NULL) //문법단계나 tokenize단에서 오류가 나면 NULL포인터로 들어온다
		return ;
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
	delete_empty_token(head); //토큰을 전부 순회하면서 빈 문자열이 있는 토큰들을 제거해준다
}
//envp -> hi=123
// echo $hi abc -> echo 123 abc
// echo "$hi" -> echo "123"
// echo "$hi"c -> echo "123"c -> echo 123c