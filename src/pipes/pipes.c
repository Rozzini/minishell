/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:37:03 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/29 02:58:42 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int make_baby_pipe(int *prev_new_fd, t_cmd *cmd, t_env **env)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (prev_new_fd[0] != 0)
		{
			dup2(prev_new_fd[0], STDIN_FILENO);
			close(prev_new_fd[0]);
		}
		if (prev_new_fd[1] != 1)
		{
			dup2(prev_new_fd[1], STDOUT_FILENO);
			close(prev_new_fd[1]);
		}
		if (cmd->input || cmd->output)
			return (exec_redir(cmd, env));
		else
		return (ft_execs(cmd, env));
	}
	return (pid);
}

void exec_pipes(t_cmd *cmd, t_env **env)
{
	int fd[2];
	int prev_new_fd[2];
	int i;
	pid_t pid;
	t_cmd *curr_cmd;

	prev_new_fd[0] = 0;
	i = 1;
	curr_cmd = cmd;
	while (curr_cmd->next != NULL)
	{
		pipe(fd);
		prev_new_fd[1] = fd[1];
		pid = make_baby_pipe(prev_new_fd, curr_cmd, env);
		if (pid == -1)
		{
			printf("fork error");
			return ;
		}
		close(fd[1]);
		prev_new_fd[0] = fd[0];
		curr_cmd = curr_cmd->next;
		i++;
	}
	if (prev_new_fd[0] != 0)
		dup2(prev_new_fd[0], 0);
	close(prev_new_fd[0]);
	if (curr_cmd->output || curr_cmd->input)
		exec_redir(curr_cmd, env);
	else
		ft_execs(curr_cmd, env);
	return ;
}

