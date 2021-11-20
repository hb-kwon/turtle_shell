/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_multi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:26:31 by ysong             #+#    #+#             */
/*   Updated: 2021/11/20 14:48:41 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_rd_option(t_mini *shell, int option)
{
	t_token	*temp;
	int		in_count;
	int		out_count;

	temp = shell->cmd->token;
	in_count = 0;
	out_count = 0;
	while (temp)
	{
		if (temp->type == RD_IN || \
		temp->type == RD_HEREDOC)
			in_count++;
		if (temp->type == RD_OUT || \
		temp->type == RD_APPEND)
			out_count++;
		temp = temp->next;
	}
	if (option == 0)
		return (in_count);
	else if (option == 1)
		return (out_count);
	else
		return (-1);
}

int	rd_option_only_out(t_mini *shell, int *rd_fds)
{
	t_token	*temp;
	char	*open_file;
	int		type;

	type = 0;
	temp = shell->cmd->token;
	while (temp)
	{
		if (temp->type == RD_OUT || temp->type == RD_APPEND)
		{
			open_file = temp->arg;
			if (temp->type == RD_OUT)
				multi_redirect_out(open_file, rd_fds);
			if (temp->type == RD_APPEND)
				multi_redirect_app(open_file, rd_fds);
		}
		temp = temp->next;
	}
	(void)type;
	return (1);
}

int	rd_option_only_in(t_mini *shell, int *rd_fds)
{
	t_token	*temp;
	char	*open_file;
	int		old_fds[2];

	save_old_fds(old_fds);
	temp = shell->cmd->token;
	while (temp)
	{
		if (temp->type == RD_IN || temp->type == RD_HEREDOC)
		{
			open_file = temp->arg;
			if (temp->type == RD_IN)
				multi_redirect_in(open_file, rd_fds);
			if (temp->type == RD_HEREDOC)
			{
				multi_redirect_herdoc(shell, rd_fds, temp->arg);
				redirect_restore(rd_fds, old_fds);
			}
		}
		temp = temp->next;
	}
	return (1);
}

int	rd_option_in_and_out(t_mini *shell, int *rd_fds)
{
	t_token	*temp;
	int		last_type;

	last_type = 0;
	temp = shell->cmd->token;
	while (temp)
	{
		if (temp->type == RD_IN || temp->type == RD_HEREDOC || \
			temp->type == RD_OUT || temp->type == RD_APPEND)
			last_type = temp->type;
		temp = temp->next;
	}
	if (last_type == RD_IN || last_type == RD_HEREDOC)
	{
		rd_option_only_out(shell, rd_fds);
		rd_option_only_in(shell, rd_fds);
	}
	if (last_type == RD_OUT || last_type == RD_APPEND)
	{
		rd_option_only_in(shell, rd_fds);
		rd_option_only_out(shell, rd_fds);
	}
	return (1);
}

int	multi_rd(t_mini *shell, int *rd_fds)
{
	int	rd_in_count;
	int	rd_out_count;

	rd_in_count = count_rd_option(shell, 0);
	rd_out_count = count_rd_option(shell, 1);
	if (rd_in_count == 0)
		return (rd_option_only_out(shell, rd_fds));
	else if (rd_out_count == 0)
		return (rd_option_only_in(shell, rd_fds));
	else
		return (rd_option_in_and_out(shell, rd_fds));
	return (0);
}
