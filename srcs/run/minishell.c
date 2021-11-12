/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:24:39 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/12 16:50:08 by ysong            ###   ########.fr       */
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

static int	run_blitin(int *i, t_cmd *temp, t_mini *shell)
{
	int	temp_num;

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
		if (shell->cmd->next)
			shell->cmd = shell->cmd->next;
	}
	free_cmd(shell);
	return (1);
}

static t_mini	*malloc_shell(void)
{
	t_mini	*temp;

	temp = (t_mini *)malloc(sizeof(t_mini));
	temp->cmd = NULL;
	return (temp);
}

void	minishell(char **en)
{
	int		status;
	int		temp;
	t_mini	*shell;

	status = 1;
	while (status)
	{
		shell = malloc_shell();
		shell->envp = en;
		g_mini.envp = en;
		temp = init_line(shell);
		if (temp)
			status = run_shell(shell);
		en = shell->envp;
		free(shell);
	}
}
