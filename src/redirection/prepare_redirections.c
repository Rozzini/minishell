/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:09:10 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/20 23:09:36 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	prep_in_files(t_cmd *cmd)
{
	int		fd;
	t_rdr	*file;

	file = cmd->input;
	while (file != NULL)
	{
		if (file->type == REDL || file->type == PREPPED_HEREDOC)
			fd = (open(file->file, O_RDONLY));
		if (fd < 0)
			return ;
		if (file->args != NULL)
			update_io_args(cmd, file);
		file = file->next;
		close(fd);
	}
}

void	prep_out_files(t_cmd *cmd)
{
	int		fd;
	t_rdr	*file;

	file = cmd->output;
	while (file != NULL)
	{
		if (file->type == REDR)
			fd = (open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0666));
		else if (file->type == REDRR)
			fd = (open(file->file, O_WRONLY | O_APPEND | O_CREAT, 0666));
		if (fd < 0)
			return ;
		if (file->args != NULL)
			update_io_args(cmd, file);
		file = file->next;
		close(fd);
	}
}

void	prep_redirections(t_cmd *cmd)
{
	int	hd_c;

	hd_c = cmdline_heredogs_count(cmd);
	if (hd_c > 0)
		prep_heredogs(cmd);
	while (cmd)
	{
		if (cmd->input)
			prep_in_files(cmd);
		if (cmd->output)
			prep_out_files(cmd);
		cmd = cmd->next;
	}
}
