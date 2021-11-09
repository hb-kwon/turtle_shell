/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:24:39 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/09 22:01:53 by hkwon            ###   ########.fr       */
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
	int cnt = 0;
	status = 1;
	while (status)
	{
		shell = malloc_shell();
		if (init_line(shell))
		{
			shell->envp = en;
			g_mini.envp = en;
			status = run_shell(shell);
			en = shell->envp;
		}
		free(shell);
	}
}
