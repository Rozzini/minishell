/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:02:01 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/20 23:22:04 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	prep_heredog_helper(t_rdr *file, int fd, int heredogs)
{
	char	*line;

	line = NULL;
	while (1)
	{
		free(line);
		line = readline("> ");
		if (ft_strcmp(line, file->file) == 0)
			break ;
		if (line && heredogs == 1)
		{
			ft_putstr_fd(line, fd);
			write(fd, "\n", 1);
		}
	}
}

void	prep_heredog(t_cmd	*cmd, int heredogs)
{
	int		fd;
	t_rdr	*file;
	char	*filename;

	filename = generate_filename(g_global.rand++);
	file = cmd->input;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	while (heredogs > 0)
	{
		while (file)
		{
			if (file->type == HEREDOC)
				break ;
			file = file->next;
		}
		prep_heredog_helper(file, fd, heredogs);
		if (file->file != NULL)
			free(file->file);
		file->file = ft_strdup(filename);
		file->type = PREPPED_HEREDOC;
		file = file->next;
		heredogs--;
	}
	free(filename);
	close(fd);
}

int	*prep_heredogs(t_cmd *cmd)
{
	t_cmd	*temp;
	int		hd_c;

	temp = cmd;
	while (temp != NULL)
	{
		hd_c = heredogs_count(temp);
		if (hd_c > 0)
			prep_heredog(temp, hd_c);
		temp = temp->next;
	}
	return (0);
}
