/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:25:40 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/08 22:27:57 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	redir_left(char *filename)
{
	int	infile_fd;

	if (access(filename, F_OK))
	{
		write(2, filename, ft_strlen(filename));
		write(2, ": No such file or directory\n", 28);
		exit(1);
	}
	infile_fd = open(filename, O_RDONLY);
	if (infile_fd == -1)
		ft_error(filename, 1);
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		ft_error(DUP2_ERRMSG, 1);
	if (close(infile_fd) == -1)
		ft_error(CLOSE_ERRMSG, 1);
}

void	redir_right(char *filename)
{
	int	outfile_fd;
	int	open_flag;

	open_flag = O_RDWR | O_CREAT | O_TRUNC;
	outfile_fd = open(filename, open_flag, 0644);
	if (outfile_fd == -1)
		ft_error(filename, 1);
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		ft_error(DUP2_ERRMSG, 1);
	if (close(outfile_fd) == -1)
		ft_error(CLOSE_ERRMSG, 1);
}

void	redir_two_left(t_bundle *bundle)
{
	int	infile_fd;
	int	open_flag;

	open_flag = O_RDWR | O_CREAT;
	infile_fd = open(bundle->current_filename->content, open_flag, 0644);
	if (infile_fd == -1)
		ft_error(OPEN_ERRMSG, 1);
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		ft_error(DUP2_ERRMSG, 1);
	if (close(infile_fd) == -1)
		ft_error(CLOSE_ERRMSG, 1);
	bundle->current_filename = bundle->current_filename->next;
}

void	redir_two_right(char *filename)
{
	int	outfile_fd;
	int	open_flag;

	if (access(filename, F_OK))
	{
		write(2, filename, ft_strlen(filename));
		write(2, ": No such file or directory\n", 28);
		exit(1);
	}
	open_flag = O_RDWR | O_CREAT | O_APPEND;
	outfile_fd = open(filename, open_flag, 0644);
	if (outfile_fd == -1)
		ft_error(filename, 1);
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		ft_error(DUP2_ERRMSG, 1);
	if (close(outfile_fd) == -1)
		ft_error(CLOSE_ERRMSG, 1);
}

void	exec_redirect(t_redirect *redirect, t_bundle *bundle)
{
	if (redirect->type == REDIR_LEFT)
		redir_left(redirect->filename);
	else if (redirect->type == REDIR_RIGHT)
		redir_right(redirect->filename);
	else if (redirect->type == REDIR_TWO_LEFT)
		redir_two_left(bundle);
	else if (redirect->type == REDIR_TWO_RIGHT)
		redir_two_right(redirect->filename);
}
