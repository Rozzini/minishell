/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:38:30 by mraspors          #+#    #+#             */
/*   Updated: 2022/07/22 22:10:28 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void    init_env_list(t_env **env_list, char **env)
{
    char    **env_split;
    int     i;

    i = 0;
    while (env[i] != NULL)
    {
        env_split = ft_split(env[i], '=');
        if (env_split[1] == NULL)
            push(env_list, env_split[0], NULL);
        else
            push(env_list, env_split[0], env_split[1]);
        i++;
    }
}