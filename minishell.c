/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 02:25:11 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/23 15:54:05 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//function to create minishell prompt string
char	*make_prompt(void)
{
	char	*s;
	char	*mini;

	s = getcwd(NULL, 0);
	mini = ft_strstr(s, "/minishell");
	mini = ft_strcat(mini, "$ ");
	return (mini);
}

int	main(int argc, char **argv, char **env)
{
	t_env		*env_list;
	t_tokens	*tokens;

	env_list = NULL;
	tokens = malloc(sizeof(t_tokens));
	init_env_list(&env_list, env);
	while (1)
	{
		tokens->cmdl = readline(make_prompt());
		if (basic_parsing(tokens) == 0)
		{
			try_execute(tokens, &env_list);
		}
	}
	return (0);
}
