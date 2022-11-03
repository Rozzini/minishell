/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:37:03 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/03 20:53:17 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int make_baby_pipe(int *prev_new_fd, t_cmd *cmd, t_env **env)
{
	pid_t pid;

	if (try_parent_builtins(cmd, env) == 1)
		return (0);
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
			ft_execs(cmd, env);
	}
	return (pid);
}

void exec_pipes(t_cmd *cmd, t_env **env)
{
	int fd[2]; // fd[0]->read fd[1]->write
	int prev_new_fd[2]; //prev_new[0] is the original and prev_new[1] is the write end from fd[1]
	pid_t pid;
	t_cmd *curr_cmd;

	//first process  getS input from the stdin->0
	prev_new_fd[0] = STDIN_FILENO;
	curr_cmd = cmd;
	//make all child processes except for last which we will redirect to stdout
	// printf("	no of cmds:%d\n", n_cmd);
	while (curr_cmd->next != NULL)
	{
		if (pipe(fd) == -1)
		{
			printf("pipe fked\n");
		}
		// f[1]->write end of the pipe
		// carry `prev` from the prev iteration.
		prev_new_fd[1] = fd[1]; // ***
		pid = make_baby_pipe(prev_new_fd, curr_cmd, env);
		if (pid == -1)
		{
			printf("fork error");
			return ;
		}
		//no need for write end bcz child process will use it
		close(fd[1]);
		//save fd[0] to give it to next child
		prev_new_fd[0] = fd[0];
		curr_cmd = curr_cmd->next;
	}
	printf("hi\ncmd:%s\n",curr_cmd->args[0]);
	//last cmd on pipe: set stdin be the read end of the prev pipe
	//and output to the original STDOUT
	// if (prev_new_fd[0] != 0)
		dup2(prev_new_fd[0], STDIN_FILENO);
	close(prev_new_fd[0]);
	if (curr_cmd->output || curr_cmd->input)
		exec_redir(curr_cmd, env);
	else
	{
		if (try_parent_builtins(cmd, env) == 1)
			return ;
		ft_execs(curr_cmd, env);
	}
	return ;
}
