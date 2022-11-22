/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:02:01 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/21 16:46:47 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*heredog_expansion(char *s, t_env **env)
{
	t_parsing	*prs;

	prs = malloc(sizeof(t_parsing));
	prs->og_token = ft_strdup(s);
	prs->token = ft_strdup(s);
	prs->exp_name = malloc(sizeof(char *) * (exp_count(s) + 1));
	prs->exp_name[0] = NULL;
	prs->iter = 0;
	prs->i = 0;
	save_exp_data(s, prs);
	prs->exp_name[prs->iter] = NULL;
	do_expansion(prs, env);
	free(s);
	s = ft_strdup(prs->token);
	free_parsing(prs);
	return (s);
}

void	prep_heredog_helper(t_rdr *file, int fd, int heredogs, t_env **env)
{
	char	*line;

	line = NULL;
	while (1)
	{
		if (line != NULL)
			free(line);
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, file->file) == 0)
			break ;
		line = heredog_expansion(line, env);
		if (line && heredogs == 1)
		{
			ft_putstr_fd(line, fd);
			write(fd, "\n", 1);
		}
	}
}

void	prep_heredog(t_cmd	*cmd, int heredogs, t_env **env)
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
		prep_heredog_helper(file, fd, heredogs, env);
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

int	*prep_heredogs(t_cmd *cmd, t_env **env)
{
	t_cmd	*temp;
	int		hd_c;

	temp = cmd;
	while (temp != NULL)
	{
		hd_c = heredogs_count(temp);
		if (hd_c > 0)
			prep_heredog(temp, hd_c, env);
		temp = temp->next;
	}
	return (0);
}
