/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapheww <rapheww@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 22:47:45 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/24 15:12:06 by rapheww          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define USAGE "Please run the program with no arguments."

# include "GNL/get_next_line.h"
# include "libft/libft.h"
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>

extern pid_t		g_signal;

typedef struct s_env_var
{
	char			*variable;
	char			*tmp;
	char			*val;
	char			quotes;
	int				len;
	char			oldquote;
}					t_env_var;

typedef struct s_cmds
{
	char			**cmds;
	char			*infile;
	char			*outfile;
	char			*limiter;
	int				append;
	int				heredoc;
	char			**cmds_quotes;
	struct s_cmds	*next;
}					t_cmds;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				exit_code;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	int				nb_cmd;
	int				fd_in;
	int				fd_out;
	struct s_cmds	*cmds;
	int				pipe[2];
	int				pid;
	int				i;
	int				flag;
	int				state;
	int				exit_status;
	int				check_exit;
	int				index;

}					t_data;

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	char			*value_quotes;
	char			*first_quotes;
	struct s_token	*next;
}					t_token;

typedef struct s_shell
{
	t_env			*env;
	t_token			*lexer;
	t_data			*data;
}					t_shell;

typedef struct s_expand
{
	int				check;
	int				i;
	int				j;
	char			*result;
	char			tmp[2];
	char			*old_res;
	t_cmds			*first;
}					t_expand;

// BUILT-IN CMD
int					make_env_variables(char *str, t_data *data, t_env *env,
						char **result);
int					make_pwd(void);
void				make_echo(char **cmds);
int					make_export(t_env *env);
int					make_export_var(t_env **env, char **str);
void				make_env(t_env *env);
int					make_cd(t_env *env, char **str);
int					make_exit(char **str, t_data **data);
int					make_unset(t_env **env, char **str);
char				**dup_env(t_env *env, char *str);
t_env				*find_env(t_env *env, char *key);
int					is_valid_word(char *str);
int					env_update_existing(t_env *tmp, char *value, int append);

// EXEC CMD
int					is_builtin(char *cmd);
int					make_built_in(t_cmds *cmds, t_data *data, t_env *env);
void				make_bin(char **cmd, t_env *env, t_shell *shell);

// PARSING
t_data				*parse_lexer(t_token **lexer, t_shell **shell);
int					check_double_token(t_token *lexer);
int					define_cmd(t_cmds **tmp_cmds, t_token **tmp, t_data *data,
						t_shell **shell);
void				expand(t_cmds **cmds, t_env *env, t_data *data);
int					define_heredoc(t_cmds **tmp_cmds, t_token **tmp,
						t_shell **shell);
char				*append_char(char *res, char c);
char				*strjoin_free(char *s1, char *s2);
void				change_state(int *state, char **cmds_quotes, int *i, int j);
int					check_flag(char *str);
int					return_var(char **result, t_env_var var);

// FREE
void				free_env(t_env *env);
void				free_lexer(t_token *token);
void				free_cmds(t_cmds *cmds);
void				free_shell(t_shell *shell);
void				free_shell_no_env(t_shell *shell);
void				free_between_lines(t_shell *shell);
void				free_lexer_null(t_token **token);

// LEXER
void				*create_token(t_token_type type, char *value, char *value2,
						char *value3);
void				addback_token(t_token **lst, t_token *new);
int					is_separator(char c);
int					check_word(char *buffer, int *state, int *j, char c);
int					check_word_quotes(char *buffer, int *state, int *j, char c);
t_token				*start_lexer(char *str);
char				*init_read(int *j, int *state, char **tmp, char *str);
void				change_tmp(char **tmp, int state);
void				skip_space_tab(char *str, int *i);

// LAUNCH CMD
char				**build_cmd(t_token *lexer);
char				**build_cmd_quotes(t_token *token);

// START MINISHELL
int					launch_cmds(t_shell *shell);
void				minishell(t_shell *shell, struct termios g_termios);
t_env				*init_env(char **env);
int					env_getsize(t_env *env);
t_env				*env_new(char *key, char *value);
int					env_addback(t_env **env, t_env *new);
void				handler(int num);
void				heredoc_handler(int sig);

// Pipex part
char				*get_cmd(char *cmd, t_shell *shell);
char				*get_exec(char *cmd, char **envp);
char				*get_path(char *cmd, char **paths);
void				open_infile(t_data *d, t_cmds *cmds, t_shell *shell);
void				open_outfile(t_data *d, t_cmds *cmds);
void				open_heredoc(t_cmds *cmds, t_shell *shell);
void				exit_error(int error_status, t_shell *shell);
void				exit_error_full(int error_status, t_shell *shell);
void				free_strs(char *str, char **strs);
int					msg(char *str1, char *str2, int erno);
int					pipe_main(t_cmds *cmds, t_shell *shell);

#endif
