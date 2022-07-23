/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:44:22 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/23 15:23:43 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int     try_builtins(t_tokens *tokens, t_env **env)
{
    if (ft_echo(tokens) == 0 ||
        ft_pwd(tokens) == 0 ||
        ft_cd(tokens) == 0 ||
        ft_env(tokens, env) == 0)
        return (0);
    return (1);
}

void    try_execute(t_tokens *tokens, t_env **env)
{
    if (try_builtins(tokens, env) == 0)
        return ;
    printf("FORK \n");
}