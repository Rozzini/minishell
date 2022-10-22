/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 22:14:22 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/21 20:12:39 by mraspors         ###   ########.fr       */
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

int	copy_expansion_name(char *s, t_parsing *prs, int i)
{
	int			start;

	i++;
	start = i;
	if (ft_isalpha(s[i]) != 0)
	{
		while (is_separator(s[i]) == 0 && ft_isalnum(s[i]) == 1 && s[i] != '\0')
			i++;
	}
	if (i != start)
		prs->exp_name[prs->iter] = ft_substr(&s[start], 0,
				ft_strlen(&s[start]) - ft_strlen(&s[i]));
	else
		prs->exp_name[prs->iter] = NULL;
	printf("EXPANSION NAME: %s\n", prs->exp_name[prs->iter]);
	prs->iter++;
	return (i);
}

t_env	*check_expansion_name(char *name, t_env **env)
{
	t_env	*temp;

	if (name == NULL)
		return (NULL);
	temp = find_node_by_key(*env, name);
	if (temp == NULL)
		return (NULL);
	return (temp);
}

void	do_expansion_helper(int *i, t_parsing *prs, t_env **env)
{
	t_env	*temp;

	if (prs->s != NULL)
		free (prs->s);
	temp = check_expansion_name(prs->exp_name[prs->c], env);
	prs->s = ft_substr(prs->token, 0,
			ft_strlen(prs->token) - ft_strlen(&(prs->token[*i])));
	printf("s: %s\n", prs->s);
	if (temp != NULL)
		prs->s = ft_strjoin(prs->s, temp->val);
	printf("s: %s\n", prs->s);
	prs->s = ft_strjoin(prs->s, &(prs->token[*i + 1
				+ ft_strlen(prs->exp_name[prs->c])]));
	printf("s: %s\n", prs->s);
	free(prs->token);
	prs->token = prs->s;
	if (temp != NULL)
		*i += ft_strlen(temp->val) - 1;
	prs->j += ft_strlen(prs->exp_name[prs->c]);
	prs->c++;
}

void	do_expansion(t_parsing	*prs, t_env **env)
{
	int		i;

	i = 0;
	prs->s = NULL;
	prs->c = 0;
	prs->j = 0;
	printf("iter: %d\n", prs->iter);
	printf("OG: %s\n", prs->og_token);
	printf("TK: %s\n", prs->token);
	while (prs->c < prs->iter)
	{
		if (prs->og_token[prs->j] == 34)
			prs->j++;
		if (prs->og_token[prs->j] == 39)
		{
			prs->j++;
			while (prs->og_token[prs->j] != 39)
			{
				i++;
				prs->j++;
			}
			prs->j++;
		}
		if (prs->token[i] == '$')
			do_expansion_helper(&i, prs, env);
		i++;
		prs->j++;
	}
}
