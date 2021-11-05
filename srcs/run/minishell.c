/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:24:39 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/05 03:57:58 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** NONE 0
** CMD 1
** REDIRECT 2
** PIPE 4
** ARG 8
** S_QUOTE 16
** D_QUOTE 32

** RD_IN 1
** RD_OUT 2
** RD_APPEND 4
** RD_HEREDOC	8
** COMMAND 16
** ARGUMENT 32
*/
char	**ft_pipe_path(char *envp[])
{
	int		i;
	char	**paths;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
	}
	return (NULL);
}
void pipe_blt_run(int i, t_mini *shell)
{
	int temp_num;
	int status;
	int rd_fds[2];
	int old_fds[2];
	char *cmd;

	cmd = shell->cmd->token->arg;
	save_old_fds(old_fds);
	pipe(shell->cmd->fds);
	g_mini.pid = fork();
	if (g_mini.pid == 0)
	{
		pipe_process(shell);
		if (!redirect_process(shell, rd_fds))
			exit(1);
		(*blt_func(i))(shell);
		if (i == 6 && !check_cmd(cmd))
			print_error_blt(cmd);
		exit(0);
	}
	// else if (g_mini.pid == -1)
	else
	{
		wait(&status);
		if (status >> 8 != 0)
			g_mini.exit_status = status >> 8;
		redirect_close(rd_fds);
		pipe_restore(shell, old_fds);
	}
}
static int run_blitin(int *i, t_cmd *temp, t_mini *shell)
{
	int temp_num;

	temp_num = -1;
	while (++temp_num < BLTIN_NUM)
	{
		if (!ft_strcmp(temp->token->arg, blt_str(temp_num)))
		{
			run_blt(shell, temp_num);
			break ;
		}
	}
	(*i) = temp_num;
	return (0);
}
static int	run_shell(t_mini *shell)
{
	int		i;
	t_cmd	*temp;

	temp = shell->cmd;
	i = -1;
	while (temp)
	{
		run_blitin(&i, temp, shell);
		if (i >= BLTIN_NUM)
			run_inner(shell);
		temp = temp->next;
		shell->cmd = shell->cmd->next;
	}
	free_cmd(shell);
	return (1);
}

t_mini *malloc_shell()
{
	t_mini *temp;

	temp = (t_mini *)malloc(sizeof(t_mini));
	temp->cmd = NULL;
	return (temp);

}

void	minishell(char **en)
{
	int		status;
	t_mini	*shell;

	status = 1;
	while (status)
	{
		shell = malloc_shell();
		shell->envp = en;
		if (init_line(shell))
			status = run_shell(shell);
		en = shell->envp;
		free(shell);
	}
}

//keycode 값을 받아와서
//getch() -> 따로 만들어줘야한다.
//parsing -> token화 시키기
//예외처리는 큰 것부터 하고 builtin부터 동작하게 만들기


//todo
