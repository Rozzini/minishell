/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 02:25:11 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/31 23:36:56 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_env		*env_list;
	t_tokens	*tokens;

	env_list = NULL;
	argc = 0;
	if (argv == NULL)
		argc++;
	tokens = malloc(sizeof(t_tokens));
	init_env_list(&env_list, env);
	while (1)
	{
		tokens->cmdl = readline("minishell$ ");
		if (start_parsing(tokens, &env_list) == 0)
		{
			try_execute(tokens, &env_list, env);
			free(tokens->cmdl);
			free_doublptr(tokens->args);
		}		
	}
	return (0);
}
