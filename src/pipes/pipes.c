/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:37:03 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/18 18:23:20 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



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
	static int	counter;

	if (temp->pid == 0)
	{
		ft_dup2(temp, prev_fd);
		close_unused_fds(cmd, counter);
		if (try_parent_builtins(temp, env) == 1
				|| try_child_builtins(temp, env) == 1
				|| ft_strcmp(temp->args[0], "./minishell") == 0)
		{
			ft_closer(cmd);
			free_cmd(&cmd);
			free_list(env);
			exit (g_global.signal);
		}
		if (temp->input || temp->output)
			exec_redir(temp, env);
		else
			ft_execs(temp, env);
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
		g_global.signal = WEXITSTATUS(g_global.signal);
		temp = temp->next;
	}
	free_cmd(&cmd);
	free_list(env);
	exit(g_global.signal);
}
