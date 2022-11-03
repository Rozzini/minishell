/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 01:22:37 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/03 16:35:32 by alalmazr         ###   ########.fr       */
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
		if (file->args != NULL)
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
		if (file->args != NULL)
			update_in_args(cmd, file);
		return (open(file->file, O_RDONLY));
	}
	else if (file->type == PREPPED_HEREDOC)
		return (open(file->file, O_RDONLY));
	return (0);
}

//check by cmd->output.. -> next.. -> next
//the last output file gets opened and returned.
int open_files_output(t_cmd *cmd)
{
	int fd;
	t_rdr *file;

	file = cmd->output;
	while (file->next != NULL)
	{
		if (file->type == REDR)
			fd = (open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0666)); //O_TRUNC delete past shit
		else if (file->type == REDRR)
			fd = (open(file->file, O_WRONLY | O_APPEND | O_CREAT, 0666));
		if (fd < 0)
			return (1);
		// if current node has args then add them to cmd->args so they get executed right
		if (file->args != NULL)
			update_out_args(cmd, file);
		file = file->next;
		close(fd);
	}
	if (file->args != NULL)
	 	update_out_args(cmd, file);
	if (file->type == REDR)
		return (open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0666));
	else if (file->type == REDRR)
		return (open(file->file, O_WRONLY | O_APPEND | O_CREAT, 0666));
	return (0);
}

//maybe split input/output redir into diff functions
int redirect(t_cmd *cmd, t_env **env)
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
		//-------CHILD-----------
		//if cmd has outputs
		if (cmd->output)
		{
			//open needed files. last file to open will be stored in fd_out
			fd_out = open_files_output(cmd);
			if (fd_out < 0)
			{
				printf("error opening file\n");
				return (1);
			}
			//wtvr will be output to STDOUT will now be in fd_out (which is our file)
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out); //since stdout now points to fd_out we close fd_out.. no longer needed
			return (ft_execs(cmd, env)); //this will output in our new stdout which is fd_out which is our file
		}
		//if cmd has inputs
		if (cmd->input)
		{
			//open needed files. last input file will be stored in fd_in
			fd_in = open_files_input(cmd);
			if (cmd->input->type == HEREDOC)
				unlink("tmp.txt");
			if (fd_in < 0)
				return (1);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);

			return(ft_execs(cmd, env));
		}
		return (0);
	}
	else
	{
		// ----PARENT----
		close(fd_out);
		close(fd_in);
		wait(0);
	}
	return (0);
}

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
int	prep_heredog(t_cmd	*cmd, int heredogs)
{
	char	*line;
	int		fd;
	t_rdr	*file;
	int		i;

	i = 0;
	line = NULL;
	file = cmd->input;
	while (heredogs > 0)
	{
		while(file)
		{
			if (file->type == HEREDOC)
				break;
			file = file->next;
		}
		fd = open("tmp.txt", O_WRONLY | O_CREAT | O_TRUNC , 0666);
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
		close(fd);
		file = file->next;
		heredogs--;
		printf("heredogs in loop: %d\n", heredogs);
	}
	cmd->input->file = ft_strdup("tmp.txt");
	cmd->input->type = PREPPED_HEREDOC; //meaning temp file is ready to be used as input for execution
	return (0);
}


int exec_redir(t_cmd *cmd, t_env **env)
{
	// if  (check_heredoc(cmd))
	// 	return (exec_heredog(1, cmd));
	if (redirect(cmd, env) == -1)
	{
		printf("redir fork/dup error\n");
		return (1);
	}
	// 	curr_cmd = curr_cmd->next;
	// }
	return (0);
}