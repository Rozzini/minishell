/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 01:22:37 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/18 21:20:33 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	make_baby_redir(t_cmd *cmd,  t_env **env, char **path)
{
	int		fd_in;
	int		fd_out;
	pid_t	pid;

	fd_in = 0;
	fd_out = 0;
	pid = fork();
	if (pid == -1)
	{
		printf("fork error\n");
		return (0);
	}
	if (pid == 0)
	{
		printf("cmd in_type: %d		out_type: %d\n", cmd->in_type, cmd->out_type);
		if (cmd->out_type == REDR)
		{
			fd_out = open(cmd->output, O_WRONLY | O_CREAT, 0777); //instead of opening once
			//will have linked list of files to pass into a function to open and close
			//each file accordingly ---> open_files(linked_list_output, ...);
			// ls a > b > c > ...
			if (!dup2(fd_out, STDOUT_FILENO))
				return (0);
			// exec_redr(curr_cmd, env, path);
			// prep_redrr(curr_cmd, cmd->output);
		}
		if (cmd->out_type == REDRR)
		{
			fd_out = open(cmd->output, O_WRONLY | O_APPEND | O_CREAT, 0777);
			if (!dup2(fd_out, STDOUT_FILENO))
				return (0);
		}
		if (cmd->in_type == REDL)
		{
			fd_in = open(cmd->input, O_RDONLY);
			if (!dup2(fd_in, STDIN_FILENO))
				return (0);
			// exec_redrr(cmd, env, path);
		}
		if (cmd->in_type == HEREDOC)
		{
			// exec_heredoc(cmd, env, path);
		}
		if (fd_in)
			close(fd_in);
		if (fd_out)
			close(fd_out);
			wait(0);
		return (ft_execs(cmd, env, path));
		return (pid);
		 
	}
	return (pid);
}

void    exec_redir(t_cmd *cmd,  t_env **env, char **path)
{
	//int		fd[2];
	//int		fd_in;
	//int		fd_out;
	//pid_t	pid;
	t_cmd 	*curr_cmd;

	curr_cmd = cmd;
    while (curr_cmd != NULL)
	{
		if (make_baby_redir(cmd, env, path) == -1)
		{
			printf("redir fork/dup error\n");
			return ;
		}
		curr_cmd = curr_cmd->next;
	}
}