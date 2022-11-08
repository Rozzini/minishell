/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:37:03 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/08 09:54:19 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_peepeeing(int *prev_new_fd, t_cmd *cmd)
{
	if (cmd->next != NULL)
	{
		if (prev_new_fd[0] != 0)
			dup2(prev_new_fd[0], STDIN_FILENO);
		if (prev_new_fd[1] != 1)
			dup2(prev_new_fd[1], STDOUT_FILENO);
	}
	else
		dup2(prev_new_fd[0], STDIN_FILENO);
	close(prev_new_fd[0]);
	close(prev_new_fd[1]);
}

int make_baby_pipe(int *prev_new_fd, t_cmd *cmd, t_env **env)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		ft_peepeeing(prev_new_fd, cmd);
		if (try_parent_builtins(cmd, env) == 1)
			exit (g_signal);
		if (cmd->input || cmd->output)
			exec_redir(cmd, env);
		else
			ft_execs(cmd, env);
		exit(g_signal);
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
	while (cmd != NULL)
	{
		if (pipe(fd) == -1)
		{
			printf("pipe fked\n");
		}
		// f[1]->write end of the pipe
		// carry `prev` from the prev iteration.
		prev_new_fd[1] = fd[1]; // ***
		pid = make_baby_pipe(prev_new_fd, cmd, env);
		wait(0);
		if (pid == -1)
		{
			printf("fork error");
			return ;
		}
		close(fd[1]);
		//save fd[0] to give it to next child
		prev_new_fd[0] = fd[0];
		cmd = cmd->next;
	}
	close(fd[0]);
	close(fd[1]);
	wait(0);
}

// void	exec_pipes(t_cmd *cmd, t_env **env)
// {
// 	int	fd[2];
// 	pid_t pid;

//     if (cmd->next != NULL)
//     {
//         if (pipe(fd) != 0)
//             printf("Failed to create pipe");
//         if ((pid = fork()) < 0)
//             printf("Failed to fork");
//         if (pid == 0)
//         {
// 			dup2(fd[1], 1);
//     		close(fd[0]);
//     		close(fd[1]);
//    			exec_pipes(cmd, env);
//         }
//         /* Fix standard input to read end of pipe */
//         dup2(fd[0], 0);
//         close(fd[0]);
//         close(fd[1]);
//     }
//     ft_execs(cmd, env);
// }