/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 07:27:54 by ysong             #+#    #+#             */
/*   Updated: 2021/11/11 04:24:07 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_in(t_mini *shell, int *rd_fds)
{
	if (rd_fds[0] > 0)
		close(rd_fds[0]);
	rd_fds[0] = open(find_token(shell, RD_IN), O_RDONLY);
	if (rd_fds[0] == -1)
	{
		print_error2("bash :", find_token(shell, RD_IN), \
		"No such file or directory");
	}
	dup2(rd_fds[0], STDIN_FILENO);
}

static void	redirect_herdoc(t_mini *shell, int *rd_fds)
{
	char	*r;
	char	*end;

	rd_fds[0] = open(".temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	end = find_token(shell, RD_HEREDOC);
	write(1, "> ", 2);
	r = readline(g_mini.path);
	while (r)
	{
		if (ft_strcmp(r, end) == 0)
			break ;
		write(1, "> ", 2);
		write(rd_fds[0], r, strlen(r));
		write(rd_fds[0], "\n", 1);
		r = readline(g_mini.path);
	}
	rd_fds[0] = open(".temp.txt", O_RDONLY);
	dup2(rd_fds[0], STDIN_FILENO);
}

static void	redirect_out(t_mini *shell, int *rd_fds)
{
	if (rd_fds[1] > 0)
		close(rd_fds[1]);
	rd_fds[1] = open(find_token(shell, ARG), \
	O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(rd_fds[1], STDOUT_FILENO);
}

static void	redirect_app(t_mini *shell, int *rd_fds)
{
	if (rd_fds[1] > 0)
		close(rd_fds[1]);
	rd_fds[1] =	open(find_token(shell, RD_APPEND), \
	O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(rd_fds[1], STDOUT_FILENO);
}

int	redirect_process(t_mini *shell, int *rd_fds)
{
	rd_fds[0] = 0;
	rd_fds[1] = 0;
	if (find_token(shell, RD_IN))
		redirect_in(shell, rd_fds);
	else if (find_token(shell, RD_HEREDOC))
		redirect_herdoc(shell, rd_fds);
	else if (find_token(shell, RD_OUT))
		redirect_out(shell, rd_fds);
	else if (find_token(shell, RD_APPEND))
		redirect_app(shell, rd_fds);
	return (1);
}
