/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraspors <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:53:48 by mraspors          #+#    #+#             */
/*   Updated: 2022/11/22 22:38:10 by mraspors         ###   ########.fr       */
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
# include <fcntl.h>
# include <errno.h>

# include "./libft/libft.h"

# define PIPE 0
# define REDR 1
# define REDRR 2
# define REDL 3
# define HEREDOC 4
# define NONE 5
# define PREPPED_HEREDOC 6

typedef struct s_rdr
{
	int				fd_in;
	int				fd_out;
	char			*file;
	char			**args;
	int				type;
	struct s_rdr	*next;
}					t_rdr;

//main stracture where commands r stored
typedef struct s_cmd
{
	char			**args;
	int				arg_c;
	int				fd[2];
	int				pid;
	int				first_cmd;
	t_rdr			*input;
	t_rdr			*output;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

//structure for environment
typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}					t_env;

//structure for parsing
typedef struct s_tokens
{
	char		*cmdl;
	char		**args;
	int			arg_c;
	int			start;
	int			end;
	t_cmd		*last;
}				t_tokens;

//structure for parsing
typedef struct s_parsing
{
	char	*token;
	char	*og_token;
	char	**exp_name;
	int		sq;
	int		dq;
	int		i;
	int		j;
	int		c;
	int		iter;
}			t_parsing;

typedef struct s_global
{
	int	rand;
	int	signal;
	int	fd_in;
	int	fd_out;
}			t_global;

t_global	g_global;

//====================BUILTINS=====================//

//for now returns 0 if successfully executed
//returns 1 if not executed
int		ft_echo(t_cmd *cmd);

int		ft_pwd(void);

int		ft_env(t_env **env_list);

int		ft_exit(t_cmd *cmd, t_env **env_list);

int		ft_cd(t_cmd *cmd, t_env **env_list);

int		ft_export(t_cmd *cmd, t_env **env_list);

void	get_push_export_d(char	*s, t_env	**export_d);

int		ft_unset(t_cmd *cmd, t_env **env_list);

int		try_parent_builtins(t_cmd *cmd, t_env **env);

int		try_child_builtins(t_cmd *cmd, t_env **env);

void	ft_cd_helper(t_env **env_list, t_env *home);

//=================================================//

//====================ENV_LIST=====================//
//duplicates env variables into list t_env
void	init_env_list(t_env **env_list, char **env);

//prints duplicated env variables
void	print_env(t_env **head);

//prints env for export builtin
int		print_env_export(t_env **head);

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
void	try_execute(t_cmd **commands, t_env **env);

//tries to execute builtins
//if one of them executed successfully returns 0;
//else returns 1;
void	try_builtins(t_cmd *cmd, t_env **env);

//executes non builtins
void	ft_execs(t_cmd *cmd, t_env **env);

//==================================================//

//================PIPES_REDIRECTIONS================//

void	exec_pipes(t_cmd *cmd, t_env **env);

void	exec_redir(t_cmd *cmd, t_env **env);

int		make_baby_redir(t_cmd *cmd, t_env **env);

void	update_io_args(t_cmd *cmd, t_rdr *file);

int		array_size(char **arr);

int		check_heredoc(t_cmd	*cmd);

int		exec_heredog(int fd, t_cmd	*cmd);

void	cur_cmd_cpy(t_cmd **head_ref, t_cmd *cmd);

//==================================================//

//=====================PARSING======================//
//returns 1 if string have opened quote
//returns 0 if everything fine
int		check_q(char *s);

//temp function
//just splits arguments and count them
int		start_parsing(t_tokens *tokens, t_env **env, t_cmd **cmd);

void	start_pipes_parsing(t_tokens *tokens, t_cmd **cmd);
//function for export builtin parsing
//returns 1 if smthing is wrong
//returns 0 if all good
int		parse_export(t_env *export_d, t_env **env_list);

char	*tokens_q_iter(char *s);

//generates list of separate tokens
void	count_tokens(char *string, t_tokens *tokens);

//return 1 if char is separator
//return 0 if not
int		is_separator(char c);

//removes quotes and does expansion
void	quotes_exp_check(t_tokens *tokens, t_env **env);

char	*count_save_tokens_iteration(int *special, char *s);

//==================================================//

//=================PARSING_HELPERS==================//

int		is_separator(char c);

int		is_special(char *s);

int		check_type(char *s);

void	p_tokens(t_tokens *tokens);

void	p_cmd(t_cmd *cmd);

//==================================================//

//====================EXPANSION=====================//

//checks if there is such env
//returns 0 if it finds env
//returns 1 if didnt
t_env	*check_expansion_name(char *name, t_env **env);

//return string which contains expansion name
int		copy_expansion_name(char *s, t_parsing *prs, int i);

//replaces expansion name in OG string with expansion value
void	do_expansion(t_parsing	*prs, t_env **env);

void	expansion_freeing(t_env	*temp, t_parsing *prs, char	*temp_s, char *s);

int		check_if_next_expansion(char *s, t_parsing *prs);

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

//returns last element of list
t_cmd	*find_last(t_cmd **head);

//==================================================//

//======================FREE========================//

void	free_doublptr(char **s);

void	free_cmd(t_cmd **head);

void	free_list(t_env **list);

void	free_parsing(t_parsing *prs);

void	free_token(t_tokens *t);

void	free_for_start_parsing(t_tokens *tokens);
//==================================================//

int		check_minishell_exec(t_cmd *cmd, t_env **env);

void	increment_shlvl(t_env **env);

void	sig_handler(int sig);

void	push_cmd_init_data(t_cmd *new_node, t_tokens *tokens);

void	push_rdr_init_data(t_rdr *new_node, t_tokens *tokens);

void	ft_closer(t_cmd *cmd);

void	prep_heredog(t_cmd	*cmd, int heredogs, t_env **env);

int		heredogs_count(t_cmd *cmd);

int		cmdline_heredogs_count(t_cmd *cmd);

int		*prep_heredogs(t_cmd *cmd, t_env **env);

int		open_files_input(t_cmd *cmd);

int		open_files_output(t_cmd *cmd);

void	cur_cmd_cpy_rdr(t_cmd *cmd, t_rdr **input, t_rdr **output);

void	close_unused_fds(t_cmd *cmd, int counter);

void	ft_dup2(t_cmd *cmd, int *prev_fd);

int		er_rdr_no_file(char *s);

void	er_ft_execs(char *s);

void	do_export(t_env	*export_d, t_env **env_list);

int		ft_exit_helper(t_cmd *cmd);

char	*generate_filename(int rand);

int		check_heredog(t_rdr *file);

t_cmd	*get_heredog_cmd(t_cmd *cmd);

void	prep_redirections(t_cmd *cmd, t_env **env);

int		exp_count(char	*s);

void	save_exp_data(char *string, t_parsing *parsing);

int		start_parsing_err(t_tokens *tokens);

int		ft_cd_error(t_cmd *cmd, t_env **env_list, int ret);

void	create_pwd(t_env **env);
#endif
