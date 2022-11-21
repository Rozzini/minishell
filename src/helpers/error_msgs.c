/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 19:58:19 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/21 20:02:06 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	er_rdr_no_file(char *s)
{
	write(2, "minishell: ", 11);
	write(2, s, ft_strlen(s));
	write(2, ": No such file or directory\n", 28);
	return (-1);
}

void	er_ft_execs(char *s)
{
	write(2, "minishell: ", 11);
	write(2, s, ft_strlen(s));
	write(2, ": command not found\n", 20);
}

int	is_all_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (is_separator(s[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	start_parsing_err(t_tokens *tokens)
{
	if (is_all_spaces(tokens->cmdl) == 1)
	{
		free(tokens->cmdl);
		free(tokens);
		return (1);
	}
	add_history(tokens->cmdl);
	if (check_q(tokens->cmdl) == 1)
	{
		free(tokens->cmdl);
		free(tokens);
		return (1);
	}
	return (0);
}
