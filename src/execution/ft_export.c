/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:05:02 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/05 07:37:30 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	export_cat_value(t_env	*export_d, t_env **env_list)
{
	t_env	*temp;
	char	*s;

	temp = find_node_by_key(*env_list, export_d->key);
	if (temp == NULL)
		push(env_list, export_d->key, export_d->val);
	else
	{
		if (temp->val == NULL)
			temp->val = ft_strdup(export_d->val);
		else
		{
			s = ft_strdup(temp->val);
			free(temp->val);
			temp->val = ft_strjoin(s, export_d->val);
			free(s);
		}
	}
}

void	export_add_value(t_env	*export_d, t_env **env_list)
{
	t_env	*temp;

	temp = find_node_by_key(*env_list, export_d->key);
	if (temp == NULL)
		push(env_list, export_d->key, export_d->val);
	else
	{
		if (temp->val != NULL)
			free (temp->val);
		if (export_d->val != NULL)
			temp->val = ft_strdup(export_d->val);
		else
			temp->val = NULL;
	}
}

void	do_export(t_env	*export_d, t_env **env_list)
{
	t_env	*temp;
	char	*s;
	int		len;

	temp = export_d;
	while (temp != NULL)
	{
		len = ft_strlen(temp->key);
		if (temp->key[len - 1] == '+')
		{
			s = ft_substr(temp->key, 0, len - 1);
			free(temp->key);
			temp->key = ft_strdup(s);
			free(s);
			export_cat_value(temp, env_list);
		}
		else
			export_add_value(temp, env_list);
		temp = temp->next;
	}
}

int	ft_export(t_cmd *cmd, t_env **env_list)
{
	t_env	*export_d;
	int		i;

	if (cmd->arg_c == 1)
		return (0);
	else
	{
		export_d = NULL;
		i = 1;
		while (cmd->args[i] != NULL)
			get_push_export_d(cmd->args[i++], &export_d);
		if (parse_export(export_d) == 1)
		{
			free_list(&export_d);
			return (1);
		}
		do_export(export_d, env_list);
		free_list(&export_d);
	}
	return (1);
}
