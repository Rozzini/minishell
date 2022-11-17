/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:02:01 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/17 19:45:30 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cmdline_heredogs_count(t_cmd *cmd)
{
	t_cmd	*curr_cmd;
	t_rdr	*file;
	int		count;

	count = 0;
	curr_cmd = cmd;
	file = cmd->input;
	while (curr_cmd != NULL)
	{
		if (curr_cmd->input)
		{
			file = curr_cmd->input;
			while (file)
			{
				if (file->type == HEREDOC)
				{
					count++;
					break;
				}
				file = file->next;
			}
		}
		curr_cmd = curr_cmd->next;
	}
	return (count);
}

int	heredogs_count(t_cmd *cmd)
{
	int		count;

	count = 0;
	if (cmd->input)
	{
		while (cmd->input)
		{
			if (cmd->input->type == HEREDOC)
				count++;
			cmd->input = cmd->input->next;
		}
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

int check_heredog(t_rdr *file)
{
	while(file)
		{
			if (file->type == HEREDOC)
				return (1);
			file = file->next;
		}
	return (0);
}


char	*generate_filename(int rand)
{
	return (ft_strjoin("tmp",ft_itoa(rand)));
}

int	prep_heredog(t_cmd	*cmd, int heredogs)
{
	char	*line;
	int		fd;
	static int rand;
	t_rdr	*file;
	int		heredog_count;
	char	*filename;

	rand = 1;
	heredog_count = heredogs;
	line = NULL;
	filename = generate_filename((int)rand++);
	file = cmd->input;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC , 0666);
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
	cmd->input->file = ft_strdup(filename);
	cmd->input->type = PREPPED_HEREDOC; //meaning temp file is ready to be used as input for execution
	// cmd->input->type = REDL; maybe do this instead cz whatever its the same at this point
	return (fd);
}

int		*prep_heredogs(t_cmd *cmd)
{
	t_cmd	*temp;

	temp = cmd;
	while (temp != NULL)
	{
		if (temp->input)
			temp->input->fd_in = prep_heredog(cmd, heredogs_count(cmd));
		temp = temp->next;
	}
	return (0);
}