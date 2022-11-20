/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:58:11 by alalmazr          #+#    #+#             */
/*   Updated: 2022/11/20 17:10:09 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return (i);
	while (arr[i] != NULL)
		i++;
	return (i);
}

void update_io_args(t_cmd *cmd, t_rdr *file)
{
	char	**io_args;
	int		i;
	int		j;

	if (file->args == NULL)
		return ;
	io_args = NULL;
	i = 0;
	j = 0;
	io_args = malloc(sizeof(char *) * (arr_size(cmd->args) + arr_size(file->args) + 1));
	while (cmd->args[i] != NULL)
	{
		io_args[i] = ft_strdup(cmd->args[i]);
		i++;
	}
	while (file->args[j] != NULL)
	{
		io_args[i] = ft_strdup(file->args[j]);
		j++;
		i++;
	}
	io_args[i] = NULL;
	cmd->arg_c = i;
	free_doublptr(cmd->args);
	cmd->args = io_args;
}
