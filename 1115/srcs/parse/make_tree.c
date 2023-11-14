/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:25:06 by hgu               #+#    #+#             */
/*   Updated: 2023/11/14 23:17:04 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	copy_strings(char **new, char **old, int cnt)
{
	int	idx;

	idx = 0;
	while (idx < cnt)
	{
		new[idx] = old[idx];
		idx++;
	}
}

void	make_simple_cmd(t_cmd *cmd, t_token *token, t_bundle *bundle)
{
	t_simple_cmd	*tmp;
	char			**new_argv;

	tmp = cmd->simple_cmd;
	if (tmp->cmd_path == NULL)
	{
		tmp->cmd_path = token->value;
		bundle->cmd_cnt++;
	}
	tmp->argv_cnt += 1;
	new_argv = malloc(sizeof(char *) * (tmp->argv_cnt + 1));
	if (new_argv == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	copy_strings(new_argv, tmp->cmd_argv, tmp->argv_cnt - 1);
	free(tmp->cmd_argv);
	tmp->cmd_argv = new_argv;
	tmp->cmd_argv[tmp->argv_cnt - 1] = token->value;
	tmp->cmd_argv[tmp->argv_cnt] = NULL;
}

t_cmd	*make_cmd(void)
{
	t_cmd			*cmd;
	t_simple_cmd	*simple;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	simple = malloc(sizeof(t_simple_cmd));
	if (simple == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	simple->cmd_argv = NULL;
	simple->cmd_path = NULL;
	cmd->redirect_s = NULL;
	cmd->simple_cmd = simple;
	cmd->simple_cmd->argv_cnt = 0;
	return (cmd);
}

t_pipe	*make_pipe(void)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	if (pipe == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	pipe->flag = 0;
	pipe->cmd = make_cmd();
	pipe->pipe = NULL;
	return (pipe);
}
t_redirect	*make_redirect(t_token *token, t_pipe *pipe)
{
	t_redirect	*new;

	new = malloc(sizeof(t_redirect));
	if (new == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	new->type = token->type;
	if (token->next->value[0] == '\0')
	{
		pipe->flag = 1;
		free(token->next->value);
		token->next->value = NULL;
		new->filename = token->next->expansion_fail;
		write(STDERR_FILENO, new->filename, ft_strlen(new->filename));
		write(STDERR_FILENO, ": ambiguous redirect\n", 21);
		new->filename = NULL;
	}
	else if (token->next)
		new->filename = token->next->value;
	free(token->value);
	return (new);
}

void	make_redirect_s(t_redirect_s **head, t_token *token, t_pipe *pipe, t_bundle *bundle)
{
	t_redirect_s	*new;
	t_redirect_s	*tmp;

	new = malloc(sizeof(t_redirect_s));
	if (new == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	new->redirect = make_redirect(token, pipe);
	new->redirect_s = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->redirect_s)
			tmp = tmp->redirect_s;
		tmp->redirect_s = new;
	}
	if (token->next->next == NULL)
		error_pipe(pipe, bundle);
}

void	error_pipe(t_pipe *pipe, t_bundle *bundle)
{
	pipe->flag = 0;
	if (pipe->cmd->redirect_s->redirect->filename == NULL)
	{
		if (pipe->cmd->simple_cmd->cmd_path != NULL)
		{
			free_cmd(pipe->cmd);
			bundle->cmd_cnt -= 1;
			pipe->cmd = NULL;
		}
	}
}

t_pipe	*make_tree(t_token *token_head, t_bundle *bundle)
{
	t_token	*tmp;
	t_pipe	*pipe_head;
	t_pipe	*pipe;

	tmp = token_head->next;
	pipe_head = make_pipe();
	pipe = pipe_head;
	while (tmp)
	{
		if ((tmp->type == PIPE || tmp->next == NULL) && pipe->flag == 1)
		{
			error_pipe(pipe, bundle);
			if (tmp->type == PIPE)
				pipe->cmd = make_cmd();
		}
		else if (tmp->type == PIPE)
		{
			free(tmp->value);
			pipe->pipe = make_pipe();
			pipe = pipe->pipe;
		}
		else if (tmp->type >= REDIR_LEFT && tmp->type <= REDIR_TWO_RIGHT)
		{
			make_redirect_s(&(pipe->cmd->redirect_s), tmp, pipe, bundle);
			tmp = tmp->next;
			if (tmp == NULL)
				break ;
		}
		else
			make_simple_cmd(pipe->cmd, tmp, bundle);
		if (tmp->expansion_fail != NULL)
			free(tmp->expansion_fail);
		tmp = tmp->next;
	}
	return (pipe_head);
}
