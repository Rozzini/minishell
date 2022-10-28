/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:58:11 by alalmazr          #+#    #+#             */
/*   Updated: 2022/10/27 22:15:48 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	array_size(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return (0);
	while (arr[i] != NULL)
	{
		i++;
	}
	return (i);
}


void update_out_args(t_cmd *cmd, t_rdr *file)
{
	char	**og_args;
	char	**io_args;
	int		i;
	int		j;

	if (cmd->output->args[0] == NULL)
		return ;
	og_args = cmd->args;
	io_args = file->args;
	i = 0;
	j = 0;
	cmd->args = malloc(sizeof(char *) * (array_size(cmd->args) + array_size(cmd->output->args) + 1));
	if (og_args != NULL)
	{
		while (og_args[i])
		{
			cmd->args[i] = ft_strdup(og_args[i]);
			i++;
		}
	}
	while (io_args[j])
	{
		cmd->args[i] = ft_strdup(io_args[j]);
		j++;
		i++;
	}
	cmd->args[i] = NULL;
	cmd->arg_c = i;
	free_doublptr(io_args);
	free_doublptr(og_args);
}

void update_in_args(t_cmd *cmd, t_rdr *file)
{
	char	**og_args;
	char	**io_args;
	int 	i;
	int 	j;

	if (cmd->input->args[0] == NULL)
		return ;
	og_args = cmd->args;
	io_args = file->args;
	i = 0;
	j = 0;
	cmd->args = malloc(sizeof(char *)
		* (array_size(cmd->args) + array_size(cmd->input->args) + 1));
	printf("%s\n", og_args[0]);
	while (og_args[i])
	{
		cmd->args[i] = ft_strdup(og_args[i]);
		i++;
	}
	j = 0;
	while (io_args[j])
	{
		cmd->args[i] = ft_strdup(io_args[j]);
		j++;
		i++;
	}
	cmd->args[i] = NULL;
	cmd->arg_c = i;
	free_doublptr(io_args);
	free_doublptr(og_args);
}
