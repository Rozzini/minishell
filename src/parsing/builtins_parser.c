/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 22:55:11 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/27 01:11:50 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//# & ignore
//* exports everything
int	parse_export_helper(char *s)
{
	char	c;
	char	*p;

	c = 33;
	while (c <= 126)
	{
		if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '=')
			c++;
		else if (c >= 48 && c <= 57)
		{
			if (s[0] == c)
				return (1);
			c++;
		}
		else
		{
			p = ft_strchr(s, c);
			if (p != NULL)
				return (1);
			c++;
		}
	}
	return (0);
}

int	parse_export(t_tokens *tokens)
{
	int	i;

	i = 1;
	while (i < tokens->arg_c)
	{
		if (tokens->args[i][0] == '=' || tokens->args[i][0] == '+')
			return (1);
		if (parse_export_helper(tokens->args[i]) == 1)
			return (1);
		i++;
	}
	return (0);
 }
 