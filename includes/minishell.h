/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:10:37 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/11/12 01:20:14 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
// # define PATH_MAX 1024
# define BLTIN_NUM 7

# define NONE 0
# define CMD 1
# define ARG 2
# define REDIRECT 4
# define PIPE 8
# define S_QUOTE 16
# define D_QUOTE 32

# define RD_IN 1
# define RD_OUT 2
# define RD_APPEND 4
# define RD_HEREDOC	8
# define COMMAND 16
# define ARGUMENT 32

# define STDIN 			0
# define STDOUT 		1
# define STDERR 		2

typedef struct s_mini		t_mini;
typedef struct s_cmd		t_cmd;
typedef struct s_token		t_token;
typedef struct s_parse		t_parse;
typedef struct s_history	t_history;
typedef struct s_read		t_read;

/*
** parse struct
*/
struct s_parse
{
	int		i;
	int		j;
	int		k;
	int		cnt;
	char	**pstr;
};

/*
** token struct
*/
struct s_token
{
	int		type;
	char	*arg;
	t_token	*next;
	t_token	*prev;
};

/*
** cmd struct
*/
struct	s_cmd
{
	t_token	*token;
	t_cmd	*next;
	t_cmd	*prev;
	int		pipe_flag;
	int		pre_flag;
	int		re_flag;
	int		fds[2];
};

struct s_mini
{
	t_cmd			*cmd;
	int				exit_status;
	int				sig_on;
	char			*line;
	char			*path;
	char			**envp;
	pid_t			pid;
};

extern t_mini				g_mini;

int		main(int argc, char *argv[], char *envp[]);

/*
** init
*/
void	init_shell(char ***en, char *envp[]);
int		init_line(t_mini *shell);
int		init_check(char *line);
int		line_empty_space(char *line);
// void	signal_int(int sig_num);
// void	signal_quit(int sig_num);

/*
** parsing
*/
t_cmd	*parse_start(char *line);
char	**parse_line(char *line);
t_token	*parse_token(char *cmd_list);
char	**parse_token_arr(char **args, char *cmd_list);
char	*parse_token_quote(char *args);
int		parse_dquote_string(char **res, char *args, int i);
int		parse_normal_string(char **res, char *args, int i);
t_token	*make_token_list(char **args);

/*
** run
*/
void	minishell(char **en);
int		check_cmd(char *cmd);
int		run_blt(t_mini *shell, int i);
int		run_inner(t_mini *shell);
void	pipe_blt_run(int i, t_mini *shell);
int		pipe_process(t_mini *shell);
void	pipe_restore(t_mini *shell, int *old_fds);

void	child_process(t_mini *shell);
int		redirect_process(t_mini *shell, int *rd_fds);
void	redirect_close(int *rd_fds);
void	redirect_restore(int *rd_fds, int *old_fds);
void	print_error_blt(char *str);

/*
** builtin
*/
char	*blt_str(int i);
int		(*blt_func(int i))(t_mini *shell);
int		ft_echo(t_mini *shell);
int		ft_cd(t_mini *shell);
int		ft_pwd(t_mini *shell);
int		ft_export(t_mini *shell);
int		is_export_valid(char *str);
void	add_export(char *str, char **new, int i);
int		export_no_value(char *str, char ***en);
int		ft_unset(t_mini *shell);
int		ft_env(t_mini *shell);
int		ft_exit(t_mini *shell);
int		check_cmd(char *cmd);

/*
** utils
*/
char	*set_value(char *arg, int idx);
char	*find_value(char *name, char **envp);
int		turn_on_flag(int *flag, int quote, int idx);
char	**make_buff(t_mini *shell);
void	free_buff(char **buff);

char	*find_en(char *key, char **en);
char	*find_token(t_mini *shell, int type);
char	*find_path(t_mini *shell, char *cmd);
char	*find_key(char *str, int key);

int		print_error2(char *msg1, char *msg2, char *err_num);
int		print_error1(char *msg, char *err_num);

void	free_cmd(t_mini *shell);
void	ft_free_arr(char **arr);

void	save_old_fds(int *old_fds);
/*
** execute
*/
char	**execute(char **args, char **en);

int		redirect(t_mini *shell);

#endif
