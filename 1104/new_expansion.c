/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:51:10 by hgu               #+#    #+#             */
/*   Updated: 2023/11/04 17:51:40 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_token	*delete_empty_token(t_token *head)
{//토큰의 헤드는 빈문자열을 들고있다
	t_token	*before;
	t_token	*now;

	now = head->next;
	before = head;
	while (now != NULL)
	{
		printf("empty test : %s\n", now->value);
		if (now->value[0] == '\0')//토큰이 빈 문자열이면
		{
			printf("this is empty\n");
			before->next = now->next; //이전노드의 next를 현재노드의 next로 이어준다
			free(now->value); //문자열 free
			free(now); //토큰 free
			now = before;
		}
		before = now;
		now = now->next;
	}
	if (head->next == NULL)
		return (free_all_token(head));
	return (head);
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

int	dollar_with_quote(t_token *token, int close_quote)
{//"%"test
	int		idx;
	char	ch;

	idx = -1;
	ch = '\0';
	printf("close_qtuoe : %d\n",close_quote);
	while ((++idx) < close_quote)//1차로 순회하면서 quote쌍들을 제거해준다
	{
		if (ch == '\0' && (token->value[idx] == '\'' || token->value[idx] == '\"'))
			ch = token->value[idx];
		else if (ch != '\0' && token->value[idx] == ch) //닫는 quote를 찾은경우 //수정필요있음
		{
			ch = '\0';
			printf("1\n");
			token->value = new_cut_quote(token->quote_start, idx, token->value); //quote를 삭제한다
			idx = idx - 2; //단어가 2개 줄어들기 때문에 "test"'hi"같은 경우 test파트의 open = 0 close = 5가 된다
			close_quote -= 2;
		}
	}
	idx = -1;
	while (token->value[++idx])
	{
		if (token->value[idx] == token->value[close_quote])
		{
			token->value = new_cut_quote(idx, close_quote, token->value);
			break ;
		}
	}
	printf("dollar_with_quote : %s %d\n",token->value, close_quote - 2);
	return (close_quote - 2);
}

int	dollar_with_separator(t_token *token, int idx)
{//$바로뒤에 quote가 오는 경우 quote만 제거하고 확장하지 않는다
	char	*tmp;
	int		len;

	if (token->value[idx + 1] == '\'' || token->value[idx + 1] == '\"') //바로뒤가 quote인 경우
		return (dollar_with_quote(token, idx + 1));//반환값은 앞으로 탐색해야하는 idx
	len = ft_strlen(token->value) - 1;
	tmp = malloc(len); //$와 숫자를 제외하고 나머지를 워드로 취급한다
	ft_strlcpy(tmp, token->value, idx + 1); //$직전까지 copy한다
	ft_strlcat(tmp, token->value + idx + 2, len); //$+@ 이후의 값을 붙여넣는다
	free(token->value);
	token->value = tmp;
	printf("dollar_with_separator : %s %d\n",token->value, idx - 1);
	return (idx - 1); //반환값은 앞으로 탐색해야하는 idx
}

char	*new_cut_quote(int open, int close, char *target)
{ //target문자열으 받아서
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

char	*del_quote(t_token *token, char *tmp, int start, int *quote_cnt)
{//quote_cnt는 start보다 작은 지점에서 지우는 quote의 개수를 count한다
	int		idx;
	char	ch;

	idx = -1;
	ch = '\0';
	while (tmp[++idx])
	{
		if (token->quote_end < idx && ch == '\0' && (tmp[idx] == '\'' || tmp[idx] == '\"'))
		{//token->quote_end보다 큰 지점에서만 quote를 삭제한다
			ch = tmp[idx];
			token->quote_start = idx;
			if (idx < start)
				(*quote_cnt) += 1;
		}
		else if (ch != '\0' && tmp[idx] == ch) //닫는 quote를 찾은경우 //수정필요있음
		{
			ch = '\0';
			tmp = new_cut_quote(token->quote_start, idx, tmp); //quote를 삭제한다
			token->quote_end = idx - 2; //2개를 지우므로 현재인덱스보다 2개작은 지점을 quote기준으로 삼는다
			if (idx < start) //""$test의 경우 idx = 1, start = 2
				(*quote_cnt) += 1;
			idx = idx - 2; //단어가 2개 줄어들기 때문에 "test"'hi"같은 경우 test파트의 open = 0 close = 5가 된다
		}
	}
	printf("after del quote -> copy : %s \n", tmp);
	return (tmp);
}

char	*insert_envp(char *tmp, char *str, int start)
{//start는 붙여넣기할 지점의 idx
	char	*new; //여기에 tmp와 str을 합친다
	int		new_len;

	if (tmp[0] == '\0')
	{
		free(tmp);
		return (str);
	}
	new_len = ft_strlen(tmp) + ft_strlen(str) + 1;
	new = malloc(new_len);
	ft_strlcpy(new, tmp, start + 1); //$앞부분을 넣어준다
	ft_strlcat(new, str, new_len); //확장한 부분을 붙여넣는다
	ft_strlcat(new, tmp + start, new_len); //수정필요
	free(tmp);
	return (new);
}

int	case_find_in_envp(t_token *token, char *envp, int start, int cut)
{//envp에서 찾은경우 //확장하는 부분과 확장한하는 부분으로 나눈다 //확장안하는 부분에서 quote들을 모두 제거한다 //합친다
	char	*tmp; //확장하지 않는 부분들을 저장할 문자열
	char	*str; //확장결과를 저장할 문자열
	int		quote_cnt; //확장이전에 존재하는 quote의 개수를 센다
	int		len;

	str = envp + cut - start + 1; //abc=kkk에서 kkk 시작하는부분의 주소
	quote_cnt = 0;
	len = ft_strlen(str);
	tmp = malloc(ft_strlen(token->value)); //넉넉하게 이렇게 만들어둔다 //필요하면 나중에 수정할것
	ft_strlcpy(tmp, token->value, start + 1);//$앞부분까지 복사해둔다
	ft_strlcat(tmp, token->value + cut + 1, ft_strlen(token->value)); //넉넉하게 복사해둔다
	tmp = del_quote(token, tmp, start, &quote_cnt); //tmp에서 따옴표를 제거한다
	free(token->value);
	token->value = insert_envp(tmp, str, start - quote_cnt);
	return (start + len - 1 - quote_cnt); //start는 $의 인덱스 len은 확장후 길이
}

void	case_not_find_in_envp(t_token *token, int start, int cut)
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

int	new_expand(t_token *token, int start, int cut, t_bundle *bundle)
{//3가지 경우가 존재한다 1. $뒤에 영문자, _ 를 제외한게 오는경우 2. envp에서 찾지 못한경우 3. envp에서 찾아서 확장하는경우
	int	idx; //envp탐색에 사용하는 인덱스
	int	after_expansion; //확장후 탐색을 시작해야하는 index

	idx = -1;
	//if (expansion_separator(token->value[idx + 1]) == 1) //$바로뒤가 구분자이면 $와 구분자를 묶어서 지워준다
	if (token->value[start + 1] == '?' || ft_isalpha(token->value[start + 1]) == 0) //$?이거나 $뒤가 알파벳이 아니면
		return (dollar_with_separator(token, start));
	while (bundle->envp[++idx] != NULL) //문자열배열의 마지막원소는 NULL이므로 순회
	{
		printf("envp : %s start : %d cut : %d\n", bundle->envp[idx], start, cut); //05 $hi=user
		printf("token->value : %s envp : %s\n", token->value + start + 1, bundle->envp[idx]);
		if (strncmp(token->value + start + 1, bundle->envp[idx], cut - start) == 0 && bundle->envp[idx][cut - start] == '=') //envp의 명단중 하나와 일치하는 경우
		{//일치하는 경우엔 $hi@@같은 경우이면 현재 토큰이 $hi와 @@로 나뉜다, 만악 $hi가 존재하지 않으면 token을 삭제한다
			printf("find envp\n");
			after_expansion = case_find_in_envp(token, bundle->envp[idx], start, cut); //start는 $의 인덱스, cut은 마지막 문자의 인덱스
			return (after_expansion); //확장 성공하는경우 //앞으로 탐색해야하는 idx를 반환한다
		}
	}// 찾지 못했으면 $~~를 삭제한다
	case_not_find_in_envp(token, start, cut); //$~~부분을 삭제한다 //오류발생 hi$USER
	return (start - 1);
}

int	check_dollar(t_token *token, int idx, int flag, t_bundle *bundle)
{
	char	*str;
	int		cut;

	str = token->value;
	if (flag >= 0 && str[idx] == '$')//현재 인덱스가 $이면 확장을 수행한다
	{
		if (str[idx + 1] == '\0') //$하나로 끝나면 바로 종료
			return (idx);
		cut = cut_env_idx(token->value, idx); //환경변수 마지막 문자의 주소를 반환하도록 한다
		idx = new_expand(token, idx, cut, bundle);
	}
	return (idx);
}

t_token	*expansion_main(t_token *head, t_bundle *bundle)
{
	t_token *tmp;
	int		idx;
	int		flag; //flag == 1이면 큰따옴표나 따옴표밖에 있는 상태 -> 확장가능, flag == -1이면 작은 따옴표 안인 상태 -> 확장불가능

	if (head == NULL) //문법단계나 tokenize단에서 오류가 나면 NULL포인터로 들어온다
		return (NULL);
	tmp = head->next; //token의 head는 빈문자를 가지고 있음
	flag = 1; //flag : 1 이면 따옴표밖 0이면 큰 따옴표안, -1이면 작은 따옴표안
	while (tmp != NULL) //토큰을 마지막까지 탐색한다
	{
		idx = -1;
		printf("before expansion token : %s\n",tmp->value);
		while (tmp->value[++idx] != '\0') //토큰의 value 문자열을 탐색한다
		{
			if (flag == 1 && tmp->value[idx] == '\'') //작은 따옴표는 $로 확장이 불가능하므로 flag를 따로 준다
				flag = -1;
			else if (flag == 1 && tmp->value[idx] == '\"') //큰 따옴표만나면 flag 0으로
				flag = 0;
			else if (flag == 0 && tmp->value[idx] == '\"') //큰따옴표종료
				flag = 1;
			else if (flag == -1 && tmp->value[idx] == '\'')//작은 따옴표 종료
				flag = -1;
			idx = check_dollar(tmp, idx, flag, bundle); //check_dollar함수는 tmp->value[idx] == '$'이면 확장을 수행하고 마지막 지점의 idx반환
			printf("idx : %d value : %s\n",idx, tmp->value);		
		}
		printf("after expansion token : %s\n",tmp->value);
		tmp = tmp->next; //만약 현재 token에서 $를 발견하면 확장 -> 
	}
	return (delete_empty_token(head)); //토큰을 전부 순회하면서 빈 문자열이 있는 토큰들을 제거해준다
}
