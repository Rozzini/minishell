/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 01:22:37 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/21 17:54:49 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	make_baby_redir(t_cmd *cmd, t_env **env, char **path)
// {
// 	int		fd;
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (cmd->out_type == REDR)
// 		{
// 			fd = open(cmd->output, O_WRONLY | O_CREAT, 0777);
// 			if (!dup2(fd, STDOUT_FILENO))
// 				return (-1);
// 		}
// 		if (cmd->out_type == REDRR)
// 		{
// 			fd = open(cmd->output, O_WRONLY | O_APPEND | O_CREAT, 0777);
// 			if (!dup2(fd, STDOUT_FILENO))
// 				return (-1);
// 		}
// 		if (cmd->in_type == REDL)
// 		{
// 			fd = open(cmd->input, O_RDONLY);
// 			if (!dup2(fd, STDIN_FILENO))
// 				return (-1);
// 		}
// 		close(fd);
// 		return (ft_execs(cmd, env, path));
// 	}
// 	return (pid);
// }

// void	exec_redir(t_cmd *cmd, t_env **env, char **path)
// {
// 	t_cmd	*curr_cmd;

// 	curr_cmd = cmd;
// 	while (curr_cmd->next != NULL)
// 	{
// 		if (make_baby_redir(cmd, env, path) == -1)
// 		{
// 			printf("redir fork/dup error\n");
// 			return ;
// 		}
// 	}
// }
