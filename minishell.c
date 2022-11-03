/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 02:25:11 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/30 02:55:29 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	base_init(t_tokens *tokens)
{
	tokens->arg_c = 0;
	tokens->args = NULL;
	tokens->cmdl = NULL;
	tokens->start = 0;
	tokens->end = 0;
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
	init_env_list(&env_list, env);
	while (1)
	{
		tokens = malloc(sizeof(t_tokens));
		base_init(tokens);
		tokens->cmdl = readline("minishell$ ");
		if (start_parsing(tokens, &env_list, &cmd) == 0)
		{
			free(tokens);
			try_execute(&cmd, &env_list);
			free_cmd(&cmd);
		}
	}
	return (0);
}
