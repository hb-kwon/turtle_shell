/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:16:49 by hkwon             #+#    #+#             */
/*   Updated: 2021/10/18 19:44:38 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_line(void)
{
	char	*line;

	line = NULL;
	get_next_line(0, &line);
	return (line);
}

void	show_prompt(void)
{
	char	buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
	write(1, buf, ft_strlen(buf));
	write(1, " > ", 3);
}

// static int	run_shell(t_mini *shell)
// {
// 	int i;

// 	i = -1;
// 	// 이부분을 t_LIST형태로 반복해야됨
// 	while (shell->cmd)
// 	{
// 		printf("token list argument check after parsing : %s\n", shell->cmd->arg);
// 		printf("token list type check after parsing : %d\n", shell->cmd->type);
// 		shell->cmd = shell->cmd->next;
// 		// if (shell->cmd->cmd == NULL)
// 		// 	shell->cmd->cmd = " ";
// 		// if (shell->pipe_flag == 0)
// 		// 	while (++i < BLTIN_NUM)
// 		// 		run_blt(shell, i);
// 		// else if (shell->re_flag == 1)
// 		// 	re_process(shell);
// 		// else
// 		// 	pipe_process(shell);
// 		// shell = shell->next;
// 	}
// 	return 1;
// }

void child_process(t_mini *shell)
{
    int     i;
	t_mini *next_shell;
	t_cmd	*temp_cmd;
	t_cmd	*temp_next_cmd;
	int ret;

	ret = EXIT_SUCCESS;

	temp_cmd = shell->cmd;
	temp_next_cmd = temp_cmd->next;

	if (temp_cmd->pipe_flag == 1)
	{
		dup2(temp_next_cmd->fds[1], STDOUT);
		close(temp_next_cmd->fds[1]);
	}
	if (temp_cmd->fds[0] != 0)
	{
		dup2(temp_cmd->fds[0], STDIN);
		close(temp_cmd->fds[0]);
	}
    i = -1;
    while (++i < BLTIN_NUM)
	{
        run_blt(shell, i);
	}
	exit(ret);
}

int pipe_process(t_mini *shell)
{
	pid_t	pid;
	int		status;
	// t_mini *next_shell;
	t_cmd	*temp_cmd;
	t_cmd	*temp_next_cmd;

	temp_cmd = shell->cmd;
	temp_next_cmd = temp_cmd->next;
	if(temp_cmd->pipe_flag == 1)
	{
		temp_next_cmd->pre_flag = 1;
		pipe(temp_next_cmd->fds);
	}
	pid = fork();
	if(pid == 0)
		child_process(shell);
	waitpid(pid, &status, 0);
	if(temp_cmd->pipe_flag == 1)
		close(temp_next_cmd->fds[1]);
	if(temp_cmd->fds[0] != 0)
		close(temp_cmd->fds[0]);
	shell->cmd = shell->cmd->next;
	return 0;
}

int re_process(t_mini *shell)
{
	char **temp;
	t_token *arg;
	temp = (char **)malloc(sizeof(char *) * 3);
	int i;
	i = 0;
	arg = shell->cmd->token;
	while (shell->cmd->token->next)
	{
		temp[i] = arg->arg;
		i++;
		arg = arg->next;
	}
}
static int	run_shell(t_mini *shell)
{
	int i;
	t_cmd *temp;

	temp = shell->cmd;
	i = -1;
	// 이부분을 t_LIST형태로 반복해야됨
	while (temp)
	{
		if (temp->token->arg == NULL)
			break ;
		if (temp->pipe_flag == 0)
			while (++i < BLTIN_NUM)
				run_blt(shell, i);
		// else if (shell->re_flag == 1)
		// 	re_process(shell);
		else
			pipe_process(shell);
		temp = temp->next;
	}
	return 1;
}
void	minishell(char **en)
{
	int		status;
	char	*line;
	t_mini	*shell;

	status = 1;
	while (status)
	{
		show_prompt();
		shell = (t_mini *)malloc(sizeof(t_mini));
		shell->envp = en;
		if (get_next_line(0, &line) > 0)
		{
			t_cmd * temp = parse_start(line);
			shell->cmd = temp;
			status = run_shell(shell);
			free(line);
		}
	}
	(void)en;
}

//keycode 값을 받아와서
//getch() -> 따로 만들어줘야한다.
//parsing -> token화 시키기
//예외처리는 큰 것부터 하고 builtin부터 동작하게 만들기
