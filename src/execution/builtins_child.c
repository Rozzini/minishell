/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:22:36 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/22 18:13:48 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_env **env_list)
{
	print_env(env_list);
	return (1);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (ft_strcmp(cmd->args[1], "-n") == 0)
	{
		flag = 1;
		i = 2;
	}	
	while (cmd->args[i] != NULL)
		printf("%s ", cmd->args[i++]);
	if (flag == 0)
		printf("\n");
	return (1);
}

int	ft_pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (s != NULL)
	{
		printf("%s\n", s);
		free(s);
	}
	return (1);
}

int	print_env_export(t_env **head)
{
	t_env	*temp;

	temp = *head;
	while (temp != NULL)
	{
		printf("declare -x ");
		if (temp->val != NULL)
		{
			if (ft_strchr(temp->val, 34) == NULL)
				printf("%s=\"%s\"\n", temp->key, temp->val);
			else
				printf("%s=%s\n", temp->key, temp->val);
		}
		else
			printf("%s\n", temp->key);
		temp = temp->next;
	}
	return (1);
}
