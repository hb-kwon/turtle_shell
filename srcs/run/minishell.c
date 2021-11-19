/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:24:39 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/19 16:04:26 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_blitin(int *i, t_mini *shell)
{
	int	temp_num;

	temp_num = -1;
	while (++temp_num < BLTIN_NUM)
	{
		if (!ft_strcmp(shell->cmd->token->arg, blt_str(temp_num)))
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
	int	i;

	i = -1;
	while (shell->cmd)
	{
		run_blitin(&i, shell);
		if (i >= BLTIN_NUM)
			run_inner(shell);
		if (shell->cmd->next)
			shell->cmd = shell->cmd->next;
		else
			break ;
	}
	free_cmd(shell);
	return (1);
}

static t_mini	*malloc_shell(void)
{
	t_mini	*temp;

	temp = (t_mini *)malloc(sizeof(t_mini));
	temp->cmd = NULL;
	temp->exit_status = 0;
	temp->sig_on = 0;
	temp->line = NULL;
	temp->path = NULL;
	temp->envp = NULL;
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
		g_mini.envp = en;
		if (init_line(shell))
			status = run_shell(shell);
		en = shell->envp;
		free(shell);
	}
}
