/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:44:26 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/08 21:12:38 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	select_err_msg(char *cmd_path)
{
	if (ft_strlen(cmd_path) >= 2 && cmd_path[0] == '.' && cmd_path[1] == '/')
	{
		ft_error(cmd_path + 2, 126);
	}
	write(2, cmd_path, ft_strlen(cmd_path));
	write(2, ": command not found\n", 20);
	exit(127);
}

void	print_cmd_not_found_err(t_simple_cmd *simple_cmd)
{
	write(2, simple_cmd->cmd_path, ft_strlen(simple_cmd->cmd_path));
	write(2, ": command not found\n", 20);
	exit(127);
}
