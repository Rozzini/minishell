/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 01:22:37 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/17 21:05:00 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	make_baby(t_cmd *cmd, char **path, t_env **env)
{
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (cmd->out_type == REDR)
		{
			fd = open(cmd->output, O_WRONLY | O_CREAT, 0777); //instead of opening once
			//will have linked list of files to pass into a function to open and close
			//each file accordingly ---> open_files(linked_list_output, ...);
			// ls a > b > c > ...
			if (!dup2(fd, STDOUT_FILENO))
				return ;
			// exec_redr(curr_cmd, env, path);
			// prep_redrr(curr_cmd, cmd->output);
		}
		if (cmd->out_type == REDRR)
		{
			fd = open(cmd->output, O_WRONLY | O_APPEND | O_CREAT, 0777);
			if (!dup2(fd, STDOUT_FILENO))
				return ;
		}
		if (cmd->in_type == REDL)
		{
			fd = open(cmd->input, O_RDONLY);
			if (!dup2(fd, STDIN_FILENO))
				return ;
			// exec_redrr(cmd, env, path);
		}
		if (cmd->in_type == HEREDOC)
		{
			// exec_heredoc(cmd, env, path);
		}
		close(fd);
		return (ft_execs(cmd, env, path));
	}
}

void    exec_redir(t_cmd *cmd, char **path, t_env **env)
{
	int		fd[2];
	int		fd_in;
	int		fd_out;
	pid_t	pid;
	t_cmd 	*curr_cmd;

	curr_cmd = cmd;
    while (curr_cmd->next != NULL)
	{

	}
}