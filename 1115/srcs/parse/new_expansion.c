/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:51:10 by hgu               #+#    #+#             */
/*   Updated: 2023/11/14 22:53:30 by hgu              ###   ########.fr       */
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

int	cut_env_idx(t_token *token, char *value, int idx)
{
	int	end_point;

	end_point = idx;
	while (value[++end_point])
	{
		if (expansion_separator(value[end_point]))
			break ;
		if (end_point == token->quote_end)
		{
			printf("cut test : %s %d\n", token->value, end_point);
			return (end_point);
		}
	}
	return (end_point - 1);
}

char	*delete_only_dollar(char *value, int dollar)
{
	char	*str;
	int		len;

	len = ft_strlen(value);
	str = malloc(len);
	if (str == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(str, value, dollar + 1);
	ft_strlcat(str, value + dollar + 1, len);
	free(value);
	return (str);
}

int	dollar_with_quote(t_token *token, int close_quote)
{
	int		idx;
	char	ch;

	idx = token->quote_end;
	ch = '\0';
	printf("%d\n",close_quote);
	del_quote_before_close_quote(token, &close_quote, idx, ch);
	idx = token->quote_end;
	while (++idx < close_quote)
	{
		if (token->value[idx] == token->value[close_quote])
		{
			token->value = new_cut_quote(idx, close_quote, token->value);
			if (idx < close_quote)
				close_quote -= 1;
			return (close_quote - 1);
		}
	}
	find_close_quote_with_dollar(token, &close_quote);
	return (close_quote - 2);
}

void	del_quote_before_close_quote(t_token *token, int *close_quote, int idx, char ch)
{
	while ((++idx) < *close_quote)
	{
		if (ch == '\0' && (token->value[idx] == '\'' || \
		token->value[idx] == '\"'))
		{
			ch = token->value[idx];
			token->quote_start = idx;
		}
		else if (ch != '\0' && token->value[idx] == ch)
		{
			ch = '\0';
			token->value = new_cut_quote(token->quote_start, idx, token->value);
			token->quote_end = idx - 2;
			idx = idx - 2;
			*close_quote -= 2;
		}
	}
}

void	find_close_quote_with_dollar(t_token *token, int *close_quote)
{
	int	idx;

	idx = *close_quote;
	while (token->value[++idx])
	{
		if (token->value[idx] == token->value[*close_quote])
		{
			token->value = new_cut_quote(*close_quote, idx, token->value);
			token->quote_end = idx - 2;
			if (idx < *close_quote)
				*close_quote -= 1;
			token->value = delete_only_dollar(token->value, *close_quote - 1);
			break ;
		}
	}
}

int	dollar_with_dollar(t_token *token, int idx)
{
	char	*pid;
	char	*tmp;
	int		len;
	int		malloc_size;

	pid = ft_itoa(getpid());
	len = ft_strlen(pid);
	malloc_size = ft_strlen(token->value) - 2 + len + 1;
	tmp = malloc(malloc_size);
	if (tmp == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(tmp, token->value, idx + 1);
	ft_strlcat(tmp, pid, ft_strlen(tmp) + len + 1);
	ft_strlcat(tmp, token->value + idx + 2, malloc_size);
	free(token->value);
	free(pid);
	token->value = tmp;
	return (idx + len - 1);
}

int	dollar_with_question_mark(t_token *token, int idx)
{
	char	*exit_code;
		char	*tmp;
	int		len;
	int		malloc_size;

	exit_code = ft_itoa(g_exit_status);
	len = ft_strlen(exit_code);
	malloc_size = ft_strlen(token->value) - 2 + len + 1;
	tmp = malloc(malloc_size);
	if (tmp == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(tmp, token->value, idx + 1);
	ft_strlcat(tmp, exit_code, ft_strlen(tmp) + len + 1);
	ft_strlcat(tmp, token->value + idx + 2, malloc_size);
	free(token->value);
	free(exit_code);
	token->value = tmp;
	return (idx + len - 1);
}

int	dollar_with_separator(t_token *token, int idx)
{
	char	*tmp;
	int		len;

	if (token->value[idx + 1] == '\'' || token->value[idx + 1] == '\"')
		return (dollar_with_quote(token, idx + 1));
	else if (token->value[idx + 1] == '$')
		return (dollar_with_dollar(token, idx));
	else if (token->value[idx + 1] == '?')
		return (dollar_with_question_mark(token, idx));
	len = ft_strlen(token->value);
	tmp = malloc(len);
	if (tmp == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(tmp, token->value, idx + 1);
	ft_strlcat(tmp, token->value + idx + 1, len);
	free(token->value);
	token->value = tmp;
	return (idx - 1);
}

char	*new_cut_quote(int open, int close, char *target)
{
	char	*str;
	int		malloc_size;

	malloc_size = ft_strlen(target) - 1;
	str = malloc(ft_strlen(target) - 1);
	if (str == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(str, target, open + 1);
	ft_strlcat(str, target + open + 1, ft_strlen(str) + close - open);
	ft_strlcat(str, target + close + 1, malloc_size);
	free(target);
	return (str);
}

void	set_del_quote_value(t_token *token, int *idx, int *start, char *ch)
{
			*ch = '\0';
			token->quote_end = *idx - 2;
			*idx = *idx - 2;
			*start -= 2;
}

char	*del_quote(t_token *token, char *tmp, int start, int *quote_cnt)
{
	int		idx;
	char	ch;

	idx = token->quote_end;
	ch = '\0';
	while ((ch != '\0' && tmp[idx + 1]) || (ch == '\0' && (idx + 1) < start))
	{
		idx++;
		if (token->quote_end < idx && ch == '\0' && \
		(tmp[idx] == '\'' || tmp[idx] == '\"'))
		{
			token->quote_start = idx;
			ch = tmp[idx];
			if (idx < start)
				(*quote_cnt) += 1;
		}
		else if (ch != '\0' && tmp[idx] == ch)
		{
			tmp = new_cut_quote(token->quote_start, idx, tmp);
			if (idx < start)
				(*quote_cnt) += 1;
			set_del_quote_value(token, &idx, &start, &ch);
		}
	}
	return (tmp);
}

void	split_after_expansion(t_token *token, char *str, char *new)
{
	int		idx;
	char	**split;
	t_token	*next;
	t_token	*tmp;

	split = ft_split(str, ' ');
	next = token->next;
	token->next = NULL;
	tmp = token;
	idx = -1;
	while (split[++idx])
	{
		if (idx == 0 && str[0]!= ' ')
			ft_strlcat(new, split[0], ft_strlen(new) + ft_strlen(split[0]) + 2);
		else
		{
			make_token(split[idx], ft_strlen(split[idx]), -1, &token);
			tmp = tmp->next;
		}
		free(split[idx]);
	}
	free(split);
	tmp->next = next;
}

char	*insert_envp(t_token *token, char *tmp, char *str, int start)
{
	char	*new;
	int		new_len;
	int		str_len;

	if (tmp[0] == '\0')
		tmp[0] = '\0';
	str_len = ft_strlen(str);
	token->quote_end += str_len;
	new_len = ft_strlen(tmp) + str_len + 1;
	new = malloc(new_len);
	if (new == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(new, tmp, start + 1);
	if (token->flag == 1)
		split_after_expansion(token, str, new);
	else
		ft_strlcat(new, str, new_len);
	ft_strlcat(new, tmp + start, new_len);
	free(tmp);
	token->expansion_idx = start + str_len;
	return (new);
}

int	case_find_in_envp(t_token *token, char *envp, int start, int cut)
{
	char	*tmp;
	char	*str;
	int		quote_cnt;
	int		len;

	token->expansion_cnt++;
	str = envp + cut - start + 1;
	quote_cnt = 0;
	len = ft_strlen(str);
	tmp = malloc(ft_strlen(token->value));
	if (tmp == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(tmp, token->value, start + 1);
	ft_strlcat(tmp, token->value + cut + 1, ft_strlen(token->value));
	tmp = del_quote(token, tmp, start, &quote_cnt); //
	free(token->value);
	token->value = insert_envp(token, tmp, str, start - quote_cnt);
	return (start + len - 1 - quote_cnt);
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

int	new_expand(t_token *token, int start, int cut, t_bundle *bundle)
{ //cut = 6
	int	idx;
	int	after_expansion;

	idx = -1;
	if (token->value[start + 1] == '?' || ft_isalpha(token->value[start + 1]) == 0)
		return (dollar_with_separator(token, start));
	while (bundle->envp[++idx] != NULL)
	{
		if (ft_strncmp(token->value + start + 1, bundle->envp[idx], cut - start) == 0 \
		&& bundle->envp[idx][cut - start] == '=')
		{
			after_expansion = case_find_in_envp(token, bundle->envp[idx], start, cut);
			return (after_expansion);
		}
	}
	case_not_find_in_envp(token, start, cut);
	return (start - 1);
}

int	check_dollar(t_token *token, int idx, t_bundle *bundle)
{
	char	*str;
	int		cut;

	str = token->value;
	if (token->flag >= 0 && str[idx] == '$')
	{
		if (str[idx + 1] == '\0')
			return (idx);
		cut = cut_env_idx(token, token->value, idx); // 6
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
	t_token *tmp;
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
			set_flag(tmp, idx);
			idx = check_dollar(tmp, idx, bundle);
		}
		check_expansion_cnt(tmp);
		tmp = tmp->next;
	}
	return (delete_empty_token(head));
}
