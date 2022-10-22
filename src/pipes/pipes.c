/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:37:03 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/22 16:45:51 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int make_baby_pipe(int *prev_new_fd, t_cmd *cmd, char **path, t_env **env)
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
			return (exec_redir(cmd, env, path));
		else
		return (ft_execs(cmd, env, path));
	}
	return (pid);
}

void exec_pipes(t_cmd *cmd, t_env **env, char **path)
{
	int fd[2]; // fd[0]->read fd[1]->write
	int prev_new_fd[2]; //prev_new[0] is the original and prev_new[1] is the write end from fd[1]
	int i; //i is not needed
	pid_t pid;
	t_cmd *curr_cmd;

	//first process  getS input from the stdin->0
	prev_new_fd[0] = 0;
	i = 1;
	curr_cmd = cmd;
	//make all child processes except for last which we will redirect to stdout
	// printf("	no of cmds:%d\n", n_cmd);
	while (curr_cmd->next != NULL)
	{
		pipe(fd);
		printf("	cmd i (%d): %s\n", i, curr_cmd->args[0]);
		// f[1]->write end of the pipe
		// carry `prev` from the prev iteration.
		prev_new_fd[1] = fd[1]; // ***
		pid = make_baby_pipe(prev_new_fd, curr_cmd, path, env);
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
		i++;
	}
	printf("	last to execute and redirect to stdout:\n	cmd i (%d): %s\n", i, curr_cmd->args[0]);
	//last cmd on pipe: set stdin be the read end of the prev pipe
	//and output to the original STDOUT
	if (prev_new_fd[0] != 0)
		dup2(prev_new_fd[0], 0);
	close(prev_new_fd[0]);
	if (curr_cmd->output || curr_cmd->input) //APPLY AFTER FILE LIST
		exec_redir(curr_cmd, env, path);
	else
		ft_execs(curr_cmd, env, path);
	return ;
}

