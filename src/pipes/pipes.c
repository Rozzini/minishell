/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:37:03 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/16 18:00:51 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_dup2(t_cmd *cmd, int *prev_fd)
{
	if (cmd->first_cmd == 1)
	{
		close(cmd->fd[0]);
		dup2(cmd->fd[1], 1);
		close(cmd->fd[1]);
	}
	else if (cmd->next == NULL)
	{
		close(prev_fd[1]);
		dup2(prev_fd[0], 0);
		close(prev_fd[0]);
	}
	else
	{
		close(prev_fd[1]);
		close(cmd->fd[0]);
		dup2(prev_fd[0], 0);
		dup2(cmd->fd[1], 1);
		close(prev_fd[0]);
		close(cmd->fd[1]);
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

void	close_unused_fds(t_cmd *cmd, int counter)
{
	int		i;
	t_cmd	*temp;

	i = 0;
	temp = cmd;
	while (temp->next != NULL)
	{
		if (i != counter && i != counter - 1)
		{
			if (temp->fd[0] != 0)
			{
				close(temp->fd[0]);
				temp->fd[0] = 0;
			}
			if (temp->fd[1] != 0)
			{
				close(temp->fd[1]);
				temp->fd[1] = 0;
			}
		}
		temp = temp->next;
		i++;
	}	
}

void	exec_pipes_helper(t_cmd	*temp, t_cmd *cmd, t_env **env, int *prev_fd)
{
	t_cmd		*node;
	static int	counter;

	if (temp->pid == 0)
	{
		ft_dup2(temp, prev_fd);
		close_unused_fds(cmd, counter);
		cur_cmd_cpy(&node, temp);
		if (try_parent_builtins(node, env) == 1
				|| try_child_builtins(node, env) == 1
				|| ft_strcmp(node->args[0], "./minishell") == 0)
		{
			ft_closer(cmd);
			free_cmd(&cmd);
			free_list(env);
			free_cmd(&node);
			exit (g_global.signal);
		}
		free_cmd(&cmd);
		if (node->input || node->output)
			exec_redir(node, env);
		else
			ft_execs(node, env);
	}
	counter++;
	if (temp->next == NULL)
		counter = 0;
}

void	exec_pipes(t_cmd *cmd, t_env **env)
{
	t_cmd	*temp;
	int		*prev_fd;
	int		i;

	i = 0;
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
		i++;
	}
	ft_closer(cmd);
	temp = cmd;
	while (temp != NULL)
	{
		waitpid(temp->pid, &g_global.signal, 0);
		temp = temp->next;
	}
	free_cmd(&cmd);
	free_list(env);
	exit(g_global.signal);
}
