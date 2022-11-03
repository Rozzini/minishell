/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:58:11 by alalmazr          #+#    #+#             */
/*   Updated: 2022/11/01 14:35:02 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
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
	cmd->args = malloc(sizeof(char *) * (arr_size(cmd->args) + arr_size(cmd->output->args) + 1));
	while (og_args[i])
	{
		cmd->args[i] = ft_strdup(og_args[i]);
		// printf("[%d]: %s\n",i, cmd->args[i]);
		i++;
	}
	while (io_args[j])
	{
		cmd->args[i] = ft_strdup(io_args[j]);
		// printf("[%d]: %s\n",i, cmd->args[i]);
		j++;
		i++;
	}
	cmd->args[i] = NULL;
	cmd->arg_c = i;
	// printf("%s %s %s %d\n-----\n", cmd->args[0], cmd->args[1], cmd->args[2], cmd->arg_c);
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
	cmd->args = malloc(sizeof(char *) * (arr_size(cmd->args) + arr_size(cmd->input->args) + 1));
	//printf("size: %d\n", ft_2d_size(cmd->args) + ft_2d_size(cmd->input->args));
	printf("%s\n", og_args[0]);
	while (og_args[i])
	{
		cmd->args[i] = ft_strdup(og_args[i]);
		// printf("[%d]: %s\n",i, cmd->args[i]);
		i++;
	}
	j = 0;
	while (io_args[j])
	{
		cmd->args[i] = ft_strdup(io_args[j]);
		// printf("[%d]: %s\n",i, cmd->args[i]);
		j++;
		i++;
	}
	cmd->args[i] = NULL;
	cmd->arg_c = i;
	free_doublptr(io_args);
	free_doublptr(og_args);
}
