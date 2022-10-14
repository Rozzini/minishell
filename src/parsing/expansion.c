/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 22:14:22 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/14 15:42:28 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_expansion_pointers(t_parsing *prs)
{
	int	i;

	i = 0;
	while (prs->exp_name[i] != NULL)
		i++;
	return (i);
}

void	add_exp_skip(t_parsing *parsing, int i)
{
	static int	i;

	parsing
	i++;
}

int		copy_expansion_name(char *s, t_parsing *prs, int i)
{
	int			start;

	i++;
	start = i;
	if (ft_isdigit(s[i]) == 0)
	{
		while (is_separator(s[i]) == 0 && ft_isalnum(s[i]) == 1 && s[i] != '\0')
			i++;
	}
	prs->exp_name[prs->iter] = ft_substr(&s[start], 0, ft_strlen(&s[start]) - ft_strlen(&s[i]));
	prs->iter++;
	return (i);
}

t_env	*check_expansion_name(char *name, t_env **env)
{
	t_env	*temp;

	temp = find_node_by_key(*env, name);
	if (temp == NULL)
		return (NULL);
	return (temp);
}

void	do_expansion(t_parsing	*prs, t_env **env)
{
	int		i;
	int		c;
	char	*s;
	t_env	*temp;

	i = 0;
	c = 0;
	while (prs->exp_name[c] != NULL)
	{
		printf("i: %d c: %c\n", i, prs->token[i]);
		if (prs->token[i] == '$')
		{
			temp = check_expansion_name(prs->exp_name[c], env);
			s = ft_substr(prs->token, 0,
				ft_strlen(prs->token) - ft_strlen(&(prs->token[i])));
			if (temp != NULL)
		 		s = ft_strjoin(s, temp->val);
			s = ft_strjoin(s, &(prs->token[i + 1 + ft_strlen(prs->exp_name[c])]));
			free(prs->token);
			prs->token = s;
			c++;
		}
		i++;
	}
}
