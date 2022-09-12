/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 02:25:11 by mraspors          #+#    #+#             */
/*   Updated: 2022/09/12 06:19:42 by mraspors         ###   ########.fr       */
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
		while (temp->args[i] != NULL)
		{
			free(temp->args[i]);
			i++;
		}
		free (temp->args);
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

	env_list = NULL;
	cmd = NULL;
	argc = 0;
	if (argv == NULL)
		argc++;
	tokens = malloc(sizeof(t_tokens));
	init_env_list(&env_list, env);
	while (1)
	{
		tokens->cmdl = readline("minishell$ ");
		if (start_parsing(tokens, &env_list, &cmd) == 0)
		{
			try_execute(&cmd, &env_list);
			free(tokens->cmdl);
			free_cmd(&cmd);
			free_doublptr(tokens->args);
		}		
	}
	return (0);
}
