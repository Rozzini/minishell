/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 02:25:11 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/04 05:47:42 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokens_init(t_tokens *tokens)
{
	tokens = malloc(sizeof(t_tokens));
	tokens->arg_c = 0;
	tokens->args = NULL;
	tokens->cmdl = NULL;
	tokens->start = 0;
	tokens->end = 0;
}

void	signals_env_init(int argc, char **argv)
{
	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	argc = 0; 
	if (argv == NULL)
		argc++;
}

int	main(int argc, char **argv, char **env)
{
	t_env		*env_list;
	t_cmd		*cmd;
	t_tokens	*tokens;

	env_list = NULL;
	cmd = NULL;
	tokens = NULL;
	signals_env_init(argc, argv);
	init_env_list(&env_list, env);
	while (1)
	{
		tokens = malloc(sizeof(t_tokens));
	tokens->arg_c = 0;
	tokens->args = NULL;
	tokens->cmdl = NULL;
	tokens->start = 0;
	tokens->end = 0;
		tokens->cmdl = readline("minishell$ ");
		if (tokens->cmdl == NULL)
		{
			//free all shit;
			exit(0);
		}
		if (start_parsing(tokens, &env_list, &cmd) == 0)
		{
			free(tokens);
			try_execute(&cmd, &env_list);
			free_cmd(&cmd);
		}
	}
	return (0);
}
