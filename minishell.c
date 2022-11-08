/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 02:25:11 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/08 12:29:30 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokens_init(t_tokens *tokens)
{
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

void	free_token(t_tokens *t)
{
	if (t != NULL)
	{
		if (t->cmdl)
			free(t->cmdl);
		//free_doublptr(t->args);
		free(t);	
	}
}
void	check_if_ctr_d(t_tokens *tokens, t_env *env_list)
{
	if (tokens->cmdl == NULL)
	{
		free_token(tokens);
		free_list(&env_list);
		exit(0);
	}
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
	increment_shlvl(&env_list);
	while (1)
	{
		tokens = malloc(sizeof(t_tokens));
		tokens_init(tokens);
		tokens->cmdl = readline("minishell$ ");
		check_if_ctr_d(tokens, env_list);
		if (start_parsing(tokens, &env_list, &cmd) == 0)
		{
			free_token(tokens);
			try_execute(&cmd, &env_list);
			free_cmd(&cmd);
		}
		else
			free_token(tokens);
	}
	return (0);
}
