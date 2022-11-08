/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:37:03 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/08 14:23:39 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void exec_pipes(t_cmd *cmd, t_env **env)
{
    if (cmd->next != NULL)
    {
        pid_t pid;
        int input[2];
        if (pipe(input) != 0)
            printf("Failed to create pipe");
        if ((pid = fork()) < 0)
            printf("Failed to fork");
        if (pid == 0)
        {
            /* Child */
            dup2(input[1], 1);
   			close(input[0]);
    		close(input[1]);
    		exec_pipes(cmd->next, env);
        }
        /* Fix standard input to read end of pipe */
        dup2(input[0], 0);
        close(input[0]);
        close(input[1]);
    }
   ft_execs(cmd, env);
}