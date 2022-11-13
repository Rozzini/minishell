/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:37:03 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/06 21:10:45 by alalmazr         ###   ########.fr       */
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

	//first process  getS input from the stdin->0
	prev_new_fd[0] = STDIN_FILENO;
	//make all child processes except for last which we will redirect to stdout
	// printf("	no of cmds:%d\n", n_cmd);
	while (cmd->next != NULL)
	{
		if (pipe(fd) == -1)
		{
			printf("pipe fked\n");
		}
		// f[1]->write end of the pipe
		// carry `prev` from the prev iteration.
		prev_new_fd[1] = fd[1]; // ***
		pid = make_baby_pipe(prev_new_fd, cmd, env);
		if (pid == -1)
		{
			printf("fork error");
			return ;
		}
		//no need for write end bcz child process will use it
		close(fd[1]);
		//save fd[0] to give it to next child
		prev_new_fd[0] = fd[0];
		cmd = cmd->next;
	}
	//last cmd on pipe: set stdin be the read end of the prev pipe
	//and output to the original STDOUT
	// if (prev_new_fd[0] != 0)
		dup2(prev_new_fd[0], STDIN_FILENO);
	close(prev_new_fd[0]);
	if (cmd->output || cmd->input)
		exec_redir(cmd, env);
	else
	{
		if (try_parent_builtins(cmd, env) == 1)
			return ;
		ft_execs(cmd, env);
	}
	return ;
}
