/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:10:37 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/10/18 19:23:22 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <termios.h>
# include <errno.h>
# include "../libft/includes/libft.h"
# include <sys/wait.h>
// # define PATH_MAX 1024
# define BLTIN_NUM 7

# define STDIN 			0
# define STDOUT 		1
# define STDERR 		2

# define NONE 0
# define CMD 1
# define REDIRECT 2
# define PIPE 4
# define ARG 8
# define S_QUOTE 16
# define D_QUOTE 32

# define RD_IN 1
# define RD_OUT 2
# define RD_APPEND 4
# define RD_HEREDOC	8
# define COMMAND 16
# define ARGUMENT 32

typedef struct s_mini	t_mini;
typedef struct s_cmd	t_cmd;
typedef struct s_token	t_token;
typedef struct s_parse	t_parse;

struct s_parse
{
	int		i;
	int		j;
	int		k;
	int		cnt;
	char	**pstr;
};

// token struct
struct s_token
{
	int		type;
	char	*arg;
	t_token	*next;
	t_token	*prev;
};

// cmd struct
struct	s_cmd
{
	int		type;
	t_token	*token;
	t_cmd	*next;
	t_cmd	*prev;
	//임시로 만들예정스
	int		pipe_flag;
	int		pre_flag;
	int		re_flag;
	int		fds[2];
};

// 하면서 필요한 부분을 구조체에 넣어서
struct s_mini
{
	t_cmd	*cmd;
	char	**envp;
	int		exit_status;
};

int		main(int argc, char *argv[], char *envp[]);
void	minishell(char **en);

/*
** parsing
*/
t_cmd	*parse_start(char *line);
char	**parse_line(char *line);
t_token	*parse_token(char *cmd_list);
char	**parse_token_arr(char **args, char *cmd_list);
t_token	*make_token_list(char **args);

/*
** execute commands
*/
char	**execute(char **args, char **en);

/*
** builtin commands
*/
char	*blt_str(int i);
int	(*blt_func(int i))(t_mini *shell);


/*
** builtin function
*/
int		ft_echo(t_mini *shell);
int		ft_cd(t_mini *shell);
int		ft_pwd(t_mini *shell);
int		ft_export(t_mini *shell);
int		ft_unset(t_mini *shell);
int		ft_env(t_mini *shell);
int		ft_exit(t_mini *shell);

int run_blt(t_mini *shell, int i);

// utils
char	*ft_strnew(size_t size);
void	*ft_malloc(size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncat(char *s1, const char *s2, size_t n);
void	ft_strclr(char *s);
char	*ft_strcat(char *s1, const char *s2);

int print_error1(char *msg, char *err_num);
int print_error2(char *msg1, char *msg2, char *err_num);
char			*find_en(char *key, char **en);
char **make_buff(t_mini *shell);

#endif
