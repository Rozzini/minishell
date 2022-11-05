/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:22:36 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/05 07:37:12 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_cmd *cmd, t_env **env_list)
{
	print_env(env_list);
	free_cmd(&cmd);
	free_list(env_list);
	exit(0);
}

void	ft_echo(t_cmd *cmd)
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
	free_cmd(&cmd);
	exit(0);
}

void	ft_pwd(t_cmd *cmd)
{
	char	*s;

	s = getcwd(NULL, 0);
	printf("%s\n", s);
	free(s);
	free_cmd(&cmd);
	exit(0);
}

void	print_env_export(t_cmd *cmd, t_env **head)
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
	free_cmd(&cmd);
	free_list(head);
	exit(0);
}
