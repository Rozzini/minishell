/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 01:22:37 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/26 18:31:31 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//gotta read from file
int open_files_input(t_cmd *cmd)
{
	int fd;
	t_rdr *file;

	file = cmd->input;
	while (file->next != NULL)
	{
		if (file->type == REDL)
			fd = (open(file->file, O_RDONLY));
		if (fd < 0)
		{
			printf("%s: No such file or directory\n", file->file); //make it >
			return (-1);
		}
		update_in_args(cmd, file);
		file = file->next;
		close(fd);
	}
	if (file->type == REDL)
	{
		if (open(file->file, O_RDONLY) < 0)
		{
			printf("%s: No such file or directory\n", file->file); //make it >
			return (-1);
		}
		update_in_args(cmd, file);
		return (open(file->file, O_RDONLY));
	}
	// else if (file->type == HEREDOC)
	// 	return (open(file->file));
	return (0);
}


int open_files_output(t_cmd *cmd)
{
	int fd;
	t_rdr *file;

	file = cmd->output;
	while (file->next != NULL)
	{
		if (file->type == REDR)
			fd = (open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0666));
		else if (file->type == REDRR)
			fd = (open(file->file, O_WRONLY | O_APPEND | O_CREAT, 0666));
		if (fd < 0)
			return (1);
		update_out_args(cmd, file);
		file = file->next;
		close(fd);
	}
	update_out_args(cmd, file);
	if (file->type == REDR)
		return (open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0666));
	else if (file->type == REDRR)
		return (open(file->file, O_WRONLY | O_APPEND | O_CREAT, 0666));
	return (0);
}

int	temp_file(char *str, int fd)
{
	fd = open("tmp.txt", O_RDWR | O_CREAT , 0666);
	if (fd < 0)
	{
		perror("open");
		printf("Bad file\n");
		return (1);
	
	}// if (dup2(fd, STDIN_FILENO))
	// 	return (1);
	write(fd, str, ft_strlen(str));
	// close (fd);
	return (fd);
}

void	rm_tmp(t_env **env, char **path)
{
	int		i;
	char	**rm;
	char	*str;
	char	**env_s;
	// pid_t	pid;

	i = 0;
	env_s = env_list_to_string(*env);
	rm = NULL;
	// rm[0] = ft_strjoin(rm[0], "rm");
	// rm[1] = ft_strjoin(rm[1], "tmp.txt");
	rm[0] = ft_strdup("rm");
	rm[1] = ft_strdup("tmp.txt");
	rm[2] = NULL;
	// pid = fork();
	// if (pid == 0)
	// {
	while (path[i] != NULL)
	{
		str = ft_strjoin(path[i], "/");
		str = ft_strjoin(str, "rm");
		if (execve(str, rm, env_s) != -1)
			return ;
		i++;
	}
	// }
	// free_doublptr(rm);
}

void	exec_heredoc(int fd, t_cmd	*cmd, t_env **env, char **path)
{
	char	*hd_line;
	char	*hd_lines;
	int		pid;
	// int		fd;

	// fd = 0;
	hd_line = NULL;
	hd_lines = NULL;
	while (1)
	{
		hd_line = readline("> ");
		if (!ft_strcmp(hd_line, cmd->input->file))
			break ;
		hd_line = ft_strjoin(hd_line, "\n");
		hd_lines = ft_strjoin(hd_lines, hd_line);
	}
	pid = fork();
	if(pid == 0)
	{
		if (temp_file(hd_lines, fd) == 1)
		{

			printf("temp file failed\n");
			return ;
		}
		cmd->input->file = ft_strdup("tmp.txt");
		cmd->input->type = REDL;
		exec_redir(cmd, env, path);
	}	
	
	return ;
}

// void	exec_heredoc(int fd, t_cmd	*cmd, t_env **env, char **path)
// {
// 	//use gnl to read lines and dup(stdin, fd)
// 	//
// }

int redirect(t_cmd *cmd, t_env **env, char **path)
{
	pid_t pid;
	int fd_in;
	int fd_out;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	pid = fork();
	if (pid < 0)
	{
		printf("fork failed\n");
		exit(0);
	}
	else if (pid == 0)
	{
		if (cmd->output)
		{
			fd_out = open_files_output(cmd);
			if (fd_out < 0)
			{
				printf("error opening file\n");
				return (1);
			}
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
			return (ft_execs(cmd, env, path));
		}
		if (cmd->input)
		{
			if (cmd->input->type == HEREDOC)
				exec_heredoc(fd_in, cmd, env, path);
			else
			{
			fd_in = open_files_input(cmd);
			if (fd_in < 0)
				return (1);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
			return(ft_execs(cmd, env, path));
			}
		}
		return (0);
	}
	else
	{
		close(fd_out);
		close(fd_in);
		wait(0);
	}
	return (0);
}

int exec_redir(t_cmd *cmd, t_env **env, char **path)
{
	if (redirect(cmd, env, path) == -1)
	{
		printf("redir fork/dup error\n");
		return (1);
	}
	// 	curr_cmd = curr_cmd->next;
	// }
	return (0);
}
