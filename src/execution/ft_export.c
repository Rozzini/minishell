/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:05:02 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/27 01:09:37 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	export_cat_value(char *args, t_env **env_list, char *equal, char *val)
{
	char	*key;
	t_env	*temp;

	key = ft_substr(args, 0,
			ft_strlen(args) - ft_strlen(val));
	temp = find_node_by_key(*env_list, key);
	if (temp == NULL)
	{
		push(env_list, key, &equal[1]);
		free(key);
	}
	else
	{
		free(key);
		if (temp->val == NULL)
			temp->val = ft_strdup(&equal[1]);
		else
		{
			key = ft_strdup(temp->val);
			free (temp->val);
			temp->val = ft_strjoin(key, &equal[1]);
			free(key);
		}
	}
}

void	export_add_value(char *args, t_env **env_list, char *equal)
{
	char	*key;
	t_env	*temp;

	key = ft_substr(args, 0,
			ft_strlen(args) - ft_strlen(equal));
	temp = find_node_by_key(*env_list, key);
	if (temp == NULL)
		push(env_list, key, &equal[1]);
	else
	{
		if (temp->val != NULL)
			free (temp->val);
		temp->val = ft_strdup(&equal[1]);
	}
	free(key);
}

void	do_export(t_tokens *tokens, t_env **env_list)
{
	t_env	*temp;
	char	*equal;
	char	*val;
	int		i;

	i = 1;
	while (i < tokens->arg_c)
	{
		equal = ft_strchr(tokens->args[i], '=');
		if (equal == NULL)
		{
			temp = find_node_by_key(*env_list, tokens->args[i]);
			if (temp == NULL)
				push(env_list, tokens->args[i], NULL);
		}
		else
		{
			val = ft_strchr(tokens->args[i], '+');
			if (val == NULL)
				export_add_value(tokens->args[i], env_list, equal);
			else
				export_cat_value(tokens->args[i], env_list, equal, val);
		}
		i++;
	}
}

int	ft_export(t_tokens *tokens, t_env **env_list)
{
	if (ft_strcmp("export", tokens->args[0]) == 0)
	{
		if (tokens->arg_c == 1)
			print_env_export(env_list);
		else
		{
			if (parse_export(tokens) == 1)
			{
				printf("minishell: export:  not a valid identifier\n");
				return (0);
			}
			do_export(tokens, env_list);
		}
		return (0);
	}
	return (1);
}
