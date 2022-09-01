/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 02:48:36 by mraspors          #+#    #+#             */
/*   Updated: 2022/09/01 05:46:23 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//add new node to list
void	push_cmd(t_cmd **head_ref, char **args, int start, int end)
{
	t_cmd	*new_node;
	int		i;

	i = 0;
	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->args = malloc(sizeof(char *) * (end - start + 1));
	while (start <= end)
	{
		new_node->args[i] = ft_strdup(args[start]);
		i++;
		start++;
	}
	new_node->args[i] = NULL;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

void	make_commands(t_tokens *tokens, t_cmd **cmd)
{
	int	i;
	int	start;

	start = 0;
	i = 0;
	while (i < tokens->arg_c)
	{
		if (tokens[i][0] == '|')
		{
			push_cmd(cmd, tokens->args, start, i);
		}
		i++;
	}
}

int	start_pipes_parsing(t_tokens *tokens, t_cmd **cmd)
{
	return (0);
}
