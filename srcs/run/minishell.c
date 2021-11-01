/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:24:39 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/01 15:12:37 by hkwon            ###   ########.fr       */
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

static int	run_shell(t_mini *shell)
{
	int		i;
	t_cmd	*temp;

	temp = shell->cmd;
	i = -1;
	while (temp)
	{
		if (temp->token == NULL)
			break ;
		if (temp->re_flag > 0)
			redirect(shell);
		else if (temp->pipe_flag == 0)
		{
			while (++i < BLTIN_NUM)
			{
				if (!ft_strcmp(temp->token->arg, blt_str(i)))
				{
					run_blt(shell, i);
					break ;
				}
			}
			if (i >= BLTIN_NUM)
				run_inner(shell);
		}
		else
			pipe_process(shell);
		temp = temp->next;
	}
	free_cmd(shell);
	return (1);
}

void	minishell(char **en)
{
	int		status;
	t_mini	*shell;

	status = 1;
	while (status)
	{
		shell = (t_mini *)malloc(sizeof(t_mini));
		shell->envp = en;
		if (init_line(shell))
			status = run_shell(shell);
		free(shell);
	}
}

//keycode 값을 받아와서
//getch() -> 따로 만들어줘야한다.
//parsing -> token화 시키기
//예외처리는 큰 것부터 하고 builtin부터 동작하게 만들기
