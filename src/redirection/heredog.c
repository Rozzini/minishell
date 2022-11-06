/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:56:19 by alalmazr          #+#    #+#             */
/*   Updated: 2022/11/06 19:24:13 by alalmazr         ###   ########.fr       */
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
int	prep_heredog(t_cmd	*cmd, int heredogs)
{
	char	*line;
	int		fd;
	t_rdr	*file;
	int		i;

	i = 0;
	line = NULL;
	file = cmd->input;
	fd = open("tmp.txt", O_WRONLY | O_CREAT | O_TRUNC , 0666);
	while (heredogs > 0)
	{
		while(file)
		{
			if (file->type == HEREDOC)
				break;
			file = file->next;
		}
		while (1)
		{
			free(line);
			line = readline("heredoc> ");
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
		printf("heredogs in loop: %d\n", heredogs);
	}
	close(fd);
	cmd->input->file = ft_strdup("tmp.txt");
	cmd->input->type = PREPPED_HEREDOC; //meaning temp file is ready to be used as input for execution
	return (0);
}

