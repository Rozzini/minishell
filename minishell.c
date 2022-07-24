/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 02:25:11 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/24 21:28:11 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	//char **a = env_list_to_string(env_list);
int	main(int argc, char **argv, char **env)
{
	t_env		*env_list;
	t_tokens	*tokens;
	t_env		*temp;

	env_list = NULL;
	tokens = malloc(sizeof(t_tokens));
	init_env_list(&env_list, env);
	while (1)
	{
		tokens->cmdl = readline("minishell$ ");
		if (basic_parsing(tokens) == 0)
			try_execute(tokens, &env_list);
	}
	return (0);
}
