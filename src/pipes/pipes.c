/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:42:36 by alalmazr          #+#    #+#             */
/*   Updated: 2022/10/18 19:56:38 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int make_baby_pipe(int fd_in, int fd_out, t_cmd *cmd, char **path, t_env **env)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (fd_in != 0)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		if (fd_out != 1)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		return (ft_execs(cmd, env, path));
	}
	return (pid);
}

void exec_pipes(t_cmd *cmd, t_env **env, char **path, int n_cmd)
{
	int fd[2]; // fd[0]->read fd[1]->write
	int prev_fd;
	int i; //i is not needed
	pid_t pid;
	t_cmd *curr_cmd;

	//first process  getS input from the stdin->0
	prev_fd = 0;
	i = 1;
	curr_cmd = cmd;
	//make all child processes except for last which we will redirect to stdout
	printf("	no of cmds:%d\n", n_cmd);
	while (curr_cmd->next != NULL)
	{
		pipe(fd);
		printf("	cmd i (%d): %s\n", i, curr_cmd->args[0]);
		// f[1]->write end of the pipe
		// carry `prev` from the prev iteration.
		pid = make_baby_pipe(prev_fd, fd[1], curr_cmd, path, env);
		if (pid == -1)
		{
			printf("fork error");
			return ;
		}
		//no need for write end bcz child process will use it
		close(fd[1]);
		//save fd[0] to give it to next child
		prev_fd = fd[0];
		curr_cmd = curr_cmd->next;
		i++;
	}
	printf("	last to execute and redirect to stdout:\n	cmd i (%d): %s\n", i, curr_cmd->args[0]);
	//last cmd on pipe: set stdin be the read end of the prev pipe
	//and output to the original STDOUT
	if (prev_fd != 0)
		dup2(prev_fd, 0);
	ft_execs(curr_cmd, env, path);
	return;
}
