/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:24:39 by hkwon             #+#    #+#             */
/*   Updated: 2021/10/19 19:07:15 by hkwon            ###   ########.fr       */
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

static int	run_shell(t_mini shell)
{
	int		i;
	t_cmd	*temp;

	temp = shell.cmd;
	i = -1;
	// 이부분을 t_LIST형태로 반복해야됨
	while (temp)
	{
		if (temp->token->arg == NULL)
			break ;
		if (temp->pipe_flag == 0)
			while (++i < BLTIN_NUM)
				run_blt(shell, i);
		// else if (shell.re_flag == 1)
		// 	re_process(shell);
		// else
		// 	pipe_process(shell);
		temp = temp->next;
	}
	return (1);
}

void	minishell(char **en)
{
	int		status;
	char	*line;
	int		ret;
	t_mini	shell;

	status = 1;
	while (status)
	{
		shell.envp = en;
		init_line(&shell);
		//debug
		while (shell.cmd)
		{
			while (shell.cmd->token)
			{
				printf("parsing cmd argument check after return : %s\n", shell.cmd->token->arg);
				printf("parsing cmd type check after return : %d\n", shell.cmd->token->type);
				shell.cmd->token = shell.cmd->token->next;
			}
			shell.cmd = shell.cmd->next;
		}
		// end
		status = run_shell(shell);
	}
}

//keycode 값을 받아와서
//getch() -> 따로 만들어줘야한다.
//parsing -> token화 시키기
//예외처리는 큰 것부터 하고 builtin부터 동작하게 만들기