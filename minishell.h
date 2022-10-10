/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:53:48 by mraspors          #+#    #+#             */
/*   Updated: 2022/10/09 07:51:27 by mraspors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

# define PIPE 0
# define REDR 1
# define REDRR 2
# define REDL 3
# define HEREDOC 4
# define NONE 5

typedef struct s_cmd
{
	char			**args;
	char			*input;
	char			*output;
	int				arg_c;
	int				type;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_tokens
{
	char		*cmdl;
	char		**args;
	int			arg_c;
	int			start;
	int			end;
	t_cmd		*last;
}				t_tokens;

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}					t_env;

//structure for parsing
//token - holds current token
//expanions_p - array of pointers to
//				expansion that should be done
typedef struct s_parsing
{
	char	*token;
	char	*exp_name[1000];
	int		expansions_p[1000];
	int		i;
}			t_parsing;

//====================BUILTINS=====================//

//for now returns 0 if successfully executed
//returns 1 if not executed
int		ft_echo(t_cmd *cmd);

int		ft_pwd(t_cmd *cmd);

int		ft_cd(t_cmd *cmd, t_env **env_list);

int		ft_env(t_cmd *cmd, t_env **env_list);

int		ft_export(t_cmd *cmd, t_env **env_list);

int		ft_unset(t_cmd *cmd, t_env **env_list);

int		ft_exit(t_cmd *cmd, t_env **env_list);

//=================================================//

//====================ENV_LIST=====================//
//duplicates env variables into list t_env
void	init_env_list(t_env **env_list, char **env);

//prints duplicated env variables
void	print_env(t_env **head);

//prints env for export builtin
void	print_env_export(t_env **head);

//Returns node with provided key
//if there is no such key returns NULL
t_env	*find_node_by_key(t_env *lst, char *key);

//return node thats points to the node with provided key
//needs to delete node if it not head
t_env	*find_node_by_key_del(t_env *lst, char *key);

//return double char array of  env
char	**env_list_to_string(t_env *env);

//=================================================//

//====================EXECUTION=====================//
//launches execution routine
void	try_execute(t_cmd **commands, t_env **env, char **path);

//tries to execute builtins
//if one of them executed successfully returns 0;
//else returns 1;
int     try_builtins(t_cmd *cmd, t_env **env);

//executes non builtins
int		ft_execs(t_cmd *cmd, t_env **env, char **path);

//==================================================//

//=====================PARSING======================//
//returns 1 if string have opened quote
//returns 0 if everything fine
int		check_q(char *s);

//temp function
//just splits arguments and count them
int		start_parsing(t_tokens *tokens, t_env **env, t_cmd **cmd);

int		start_pipes_parsing(t_tokens *tokens, t_cmd **cmd);
//function for export builtin parsing
//returns 1 if smthing is wrong
//returns 0 if all good
int		parse_export(t_cmd *cmd);

char	*tokens_q_iter(char *s);

//generates list of separate tokens
void	count_tokens(char *string, t_tokens *tokens);

//return 1 if char is separator
//return 0 if not
int		is_separator(char c);

//removes quotes and does expansion
void	quotes_exp_check(t_tokens *tokens, t_env **env);

//==================================================//

//====================EXPANSION=====================//

//checks if there is such env
//returns 0 if it finds env
//returns 1 if didnt
t_env	*check_expansion_name(char *name, t_env **env);

//return string which contains expansion name
char	*copy_expansion_name(char *s, t_parsing *prs, int i);

//replaces expansion name in OG string with expansion value
void	do_expansion(t_parsing	*prs, t_env **env);

//==================================================//

//====================ALL_LIST======================//

//adds new node to list of env
//returns 1 if quote is not closed
void	push(t_env **head_ref, char *key, char *val);

//removes head node from list env
void	delete_head(t_env **head);

//removes provided noded
void	delete_node(t_env *node);

//return nodes count
int		count_nodes(t_env **head);

//==================================================//

//======================FREE========================//

void	free_doublptr(char **s);

void	free_list(t_env **list);

//==================================================//

int		check_minishell_exec(t_tokens	*tokens, t_env **env);

#endif
