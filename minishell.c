/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrizk <mrizk@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 02:25:11 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/27 19:30:11 by mrizk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	//char **a = env_list_to_string(env_list);
int	main(int argc, char **argv, char **env)
{
	t_env		*env_list;
	t_tokens	*tokens;
	env_list = NULL;
	tokens = malloc(sizeof(t_tokens));
	init_env_list(&env_list, env);
	if (argc > 11111111)
	{
		if (argv[1][0] == '$')
			return (0);
	}
	while (1)
	{
		tokens->cmdl = readline("minishell$ ");
		check_minishell_exec(tokens, &env_list);
		if (basic_parsing(tokens) == 0)
			try_execute(tokens, &env_list);
		if (tokens->cmdl[0] != '\0')
		{
			free(tokens->cmdl);
			free_doublptr(tokens->args);
		}
	}
	return (0);
}
