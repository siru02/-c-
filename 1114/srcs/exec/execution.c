/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:35:15 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/08 21:37:44 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	exec_tree(t_bundle *bundle, t_pipe *root)
{
	if (!root)
		return (-1);
	get_fork_cnt(bundle, root);
	if (check_one_cmd_and_builtin(root) == 1)
	{
		if (exec_one_builtin(bundle, root) == -1)
			return (-1);
		return (0);
	}
	else
		exec_command(bundle, root);
	return (0);
}

void	exec_command(t_bundle *bundle, t_pipe *root)
{
	int	idx;

	idx = -1;
	if (pre_exec_here_doc(root, bundle) == -1)
		return ;
	exec_recur(root, bundle, -1, 0);
	signal(SIGINT, sigint_handler_during_fork);
	signal(SIGQUIT, sigquit_handler_during_fork);
	if (bundle->cmd_cnt >= 1 || bundle->fork_cnt != 0)
		while (++idx < bundle->fork_cnt)
			set_exit_status(bundle);
	if (bundle->cmd_cnt == 0)
		set_exit_status(bundle);
}
