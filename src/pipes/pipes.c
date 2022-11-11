/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:37:03 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/11 19:18:12 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_dup2(t_cmd *cmd, int *prev_fd)
{
	if (cmd->first_cmd == 1)
	{
		dup2(cmd->fd[1], 1);
		close(cmd->fd[1]);
		close(cmd->fd[0]);
	}
	else if (cmd->next == NULL)
	{
		dup2(prev_fd[0], 0);
		close(prev_fd[0]);
		close(prev_fd[1]);
	}
	else
	{
		dup2(prev_fd[0], 0);
		dup2(cmd->fd[1], 1);
		close(prev_fd[1]);
		close(prev_fd[0]);
		close(cmd->fd[1]);
		close(cmd->fd[0]);
	}
}

void	create_pipes(t_cmd *cmd)
{
	t_cmd	*temp;

	temp = cmd;
	while (temp->next != NULL)
	{
		if (pipe(temp->fd) < 0)
		{
			printf("piping error\n");
			return ;
		}
		temp = temp->next;
	}
}

void	exec_pipes_helper(t_cmd	*temp, t_cmd *cmd, t_env **env, int *prev_fd)
{
	t_cmd	*node;

	if (temp->pid == 0)
	{
		ft_dup2(temp, prev_fd);
		cur_cmd_cpy(&node, temp);
		free_cmd(&cmd);
		if (try_parent_builtins(node, env) == 1)
			exit (g_signal);
		if (node->input || node->output)
			exec_redir(node, env);
		else
			ft_execs(node, env);
		exit(g_signal);
	}
}

void	exec_pipes(t_cmd *cmd, t_env **env)
{
	t_cmd	*temp;
	int		*prev_fd;

	create_pipes(cmd);
	temp = cmd;
	prev_fd = NULL;
	while (temp != NULL)
	{
		temp->pid = fork();
		if (temp->pid < 0)
			return ;
		exec_pipes_helper(temp, cmd, env, prev_fd);
		prev_fd = temp->fd;
		temp = temp->next;
	}
	ft_closer(cmd);
	temp = cmd;
	while (temp != NULL)
	{
		waitpid(temp->pid, &g_signal, 0);
		temp = temp->next;
	}
}
