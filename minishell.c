/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 02:25:11 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/21 13:23:28 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd **head)
{
	t_cmd	*temp;
	int		i;

	temp = *head;
	while (temp != NULL)
	{
		i = 0;
		free_doublptr(temp->args);
		if (temp->input != NULL)
			free (temp->input);
		if (temp->output != NULL)
			free (temp->output);
		*head = (*head)->next;
		temp = *head;
	}
	free(temp);
	*head = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_env		*env_list;
	t_cmd		*cmd;
	t_tokens	*tokens;
	char		**path;

	env_list = NULL;
	cmd = NULL;
	argc = 0;
	if (argv == NULL)
		argc++;
	tokens = malloc(sizeof(t_tokens));
	init_env_list(&env_list, env);
	path = ft_split(find_node_by_key(env_list, "PATH")->val, ':');
	while (1)
	{
		tokens->cmdl = readline("minishell$ ");
		if (start_parsing(tokens, &env_list, &cmd) == 0)
		{
			try_execute(&cmd, &env_list, path);
			free(tokens->cmdl);
			free_cmd(&cmd);
			free_doublptr(tokens->args);
		}		
	}
	return (0);
}
