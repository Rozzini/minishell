/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:02:01 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/16 18:07:26 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	heredogs_count(t_cmd *cmd)
{
	t_cmd	*curr_cmd;
	t_rdr	*file;
	int		count;

	count = 0;
	curr_cmd = cmd;
	file = cmd->input;
	while (curr_cmd != NULL)
	{
		if (cmd->input)
		{
			file = curr_cmd->input;
			while (file)
			{
				if (file->type == HEREDOC)
					count++;
				file = file->next;
			}
		}
		curr_cmd = curr_cmd->next;
	}
	return (count);
}

t_cmd	*get_heredog_cmd(t_cmd *cmd)
{
	t_cmd	*curr_cmd;
	t_rdr	*file;

	curr_cmd = cmd;
	file = cmd->input;
	while (curr_cmd != NULL)
	{
		if (cmd->input)
		{
			file = curr_cmd->input;
			while (file)
			{
				if (file->type == HEREDOC)
					return (curr_cmd);
				file = file->next;
			}
		}
		curr_cmd = curr_cmd->next;
	}
	return (0);
}

//takes one cmd with existing heredoc
//makes temp file with the input (could make it into the argument "xxx\nyyy\nzzz\n")
//changes input type for redirection to to PREPPED_HEREDOC meaning it can be passed as
//cmd < temp.txt for execution
//have to remove the temp file for types PREPPED_HEREDOC after redirection

void	reset_fd(void)
{
	dup2(g_global.sv_in, 0);
	dup2(g_global.sv_out, 1);
}

int	prep_heredog(t_cmd	*cmd, int heredogs)
{
	char	*line;
	int		fd;
	t_rdr	*file;
	int		heredog_count;

	heredog_count = heredogs;
	line = NULL;
	file = cmd->input;
	fd = open("tmp.txt", O_WRONLY | O_CREAT | O_TRUNC , 0666);
	while (heredogs > 0)
	{
		if (heredogs != heredog_count)
			reset_fd();
		while(file)
		{
			if (file->type == HEREDOC)
				break;
			file = file->next;
		}
		while (1)
		{
			free(line);
			line = readline("> ");
			if (!ft_strcmp(line, file->file))//the file is EOF here
				break ;
			if (line && heredogs == 1)
			{
				ft_putstr_fd(line, fd);
				write(fd, "\n", 1);
			}
		}
		file = file->next;
		heredogs--;
	}
	close(fd);
	cmd->input->file = ft_strdup("tmp.txt");
	cmd->input->type = PREPPED_HEREDOC; //meaning temp file is ready to be used as input for execution
	return (0);
}

// static void	fd_closer(int *fd)
// {
// 	if (fd[1] != 0)
// 	{
// 		close(fd[1]);
// 		fd[1] = 0;
// 	}
// 	if (fd[0] != 0)
// 	{
// 		close(fd[0]);
// 		fd[0] = 0;
// 	}
// }

// int	check_builtins(t_cmd *cmd)
// {
// 	if (cmd->args != NULL)
// 	{
// 		if (ft_strcmp("cd", cmd->args[0]) == 0
// 			|| strcmp("echo", cmd->args[0]) == 0
// 			|| ft_strcmp("pwd", cmd->args[0]) == 0
// 			|| ft_strcmp("env", cmd->args[0]) == 0
// 			|| ft_strcmp("unset", cmd->args[0]) == 0
// 			|| ft_strcmp("export", cmd->args[0]) == 0
// 			|| ft_strcmp("exit", cmd->args[0]) == 0)
// 			return (1);
// 	}
// 	return (0);
// }

// int	ft_here_doc(char *eof, int fd[2], t_cmd *cmd)
// {
// 	char	*buffer;

// 	buffer = ft_strdup("");
// 	// while (!ft_strcmp(eof, buffer))
// 	while (1)
// 	{
// 		free(buffer);
// 		buffer = NULL;
// 		buffer = readline("> ");
// 		if (!ft_strcmp(buffer, eof))//the file is EOF here
// 				break ;
// 		if (buffer) //write to write end of pipe
// 		{
// 			ft_putstr_fd(buffer, fd[1]);
// 			write(fd[1], "\n", 1);
// 		}
// 	}
// 	free(buffer);
// 	if (check_builtins(cmd))
// 		fd_closer(fd);
// 	return (0);
// }

// int	heredoc_exec(t_cmd *cmd, int cmd_num)
// {
// 	int	fd[2];
// 	int	status;

	
// 	pipe(fd); //pipe
// 	ft_here_doc(cmd->input->file, fd, cmd);
// 	// g_signal = WEXITSTATUS(status);
// 	// if (builtin_checker(data, cmd_num) == 0)
// 	// 	dup2(fd[0], 0); //if its a builtin dup
// 	if (!check_builtins(cmd))
// 		fd_closer(fd);
// 	// return (g_signal);
// }