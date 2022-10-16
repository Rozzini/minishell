/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalmazr <alalmazr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:42:36 by alalmazr          #+#    #+#             */
/*   Updated: 2022/10/12 22:17:01 by alalmazr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//if out_type == 2 its >>
// int	prep_redrr(t_cmd *cmd, char *out_file)
// {	
// 	int	fd;
// 	fd = open(out_file, O_APPEND | O_CREAT | O_WRONLY, 0777);
// 	if (!dup2(fd, STDOUT_FILENO))
// 	{
// 		printf("error in dup2");
// 		return (fd);
// 	}
// 	printf("done prep redrr\n");
// 	//ft_execs(cmd, env, path);
// 	return (fd);
// }
// void	exec_redr()
// {

// }




//my main process will create a pipe for child proccesses to communicate
//it will also fork and wait for them
//pipe() -> fork() for each process u want
// void exec_pipes(t_cmd *cmd, t_env **env, char **path)
// {
// 	int in_out[2];
// 	pid_t pid;

// 	printf("exec pipes:\n");
// 	// if (!cmd->next)
// 	// {
// 	// 	printf("!cmd->next:\n");
// 	// 	// if (cmd->out_type == REDR)
// 	// 	// 	exec_redr(cmd, env, path);
// 	// 	if (cmd->out_type == REDRR)
// 	// 		fd = prep_redrr(cmd, cmd->output);
// 	// 	// if (cmd->in_type == REDL)
// 	// 	// 	exec_redrr(cmd, env, path);
// 	// 	// if (cmd->in_type == HEREDOC)
// 	// 	// 	exec_heredoc(cmd, env, path);
// 	// }
// 	if (cmd->next != NULL)
// 	{
// 		if (pipe(in_out) != 0)
// 			return ;
// 		if ((pid = fork()) < 0)
// 			return ;
// 		if (pid == 0)
//         {
// 			dup2(in_out[1], STDOUT_FILENO);
//     		close(in_out[0]);
//     		close(in_out[1]);
// 			exec_pipes(cmd->next, env, path);
// 		}
// 		dup2(in_out[0], STDIN_FILENO);
//     	close(in_out[0]);
//     	close(in_out[1]);
// 	}
// 	else
// 	{
// 	printf("b4 ft_execs :)\n");
// 	ft_execs(cmd, env, path);
// 	}
//}