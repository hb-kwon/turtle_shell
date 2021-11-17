/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 07:27:54 by ysong             #+#    #+#             */
/*   Updated: 2021/11/17 18:16:56 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_in(t_mini *shell, int *rd_fds)
{
	char	*path;

	path = find_token(shell, RD_IN);
	if (access(path, R_OK) == -1 && errno == EACCES)
	{
		print_error1(path, "Permission denied");
		return (0);
	}
	if (rd_fds[0] > 0)
		close(rd_fds[0]);
	rd_fds[0] = open(find_token(shell, RD_IN), O_RDONLY);
	if (rd_fds[0] == -1)
	{
		print_error1(find_token(shell, RD_IN), \
		"No such file or directory");
		return (0);
	}
	dup2(rd_fds[0], STDIN_FILENO);
	return (1);
}

static void	redirect_herdoc(t_mini *shell, int *rd_fds)
{
	char	*r;
	char	*end;

	rd_fds[0] = open(".temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	end = find_token(shell, RD_HEREDOC);
	r = readline("> ");
	while (r)
	{
		if (ft_strcmp(r, end) == 0)
			break ;
		write(rd_fds[0], r, strlen(r));
		write(rd_fds[0], "\n", 1);
		free(r);
		r = readline("> ");
	}
	free(r);
	rd_fds[0] = open(".temp.txt", O_RDONLY);
	dup2(rd_fds[0], STDIN_FILENO);
	unlink(".temp.txt");
}

static int	redirect_out(t_mini *shell, int *rd_fds)
{
	char	*path;

	path = find_token(shell, ARG);
	if (access(path, W_OK) == -1 && errno == EACCES)
	{
		print_error1(path, ": Permission denied");
		return (0);
	}
	if (rd_fds[1] > 0)
		close(rd_fds[1]);
	rd_fds[1] = open(find_token(shell, ARG), \
	O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(rd_fds[1], STDOUT_FILENO);
	return (1);
}

static int	redirect_app(t_mini *shell, int *rd_fds)
{
	char	*path;

	path = find_token(shell, RD_APPEND);
	if (access(path, W_OK) == -1 && errno == EACCES)
	{
		print_error1(path, ": Permission denied");
		return (0);
	}
	if (rd_fds[1] > 0)
		close(rd_fds[1]);
	rd_fds[1] = open(find_token(shell, RD_APPEND), \
	O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(rd_fds[1], STDOUT_FILENO);
	return (1);
}

int	redirect_process(t_mini *shell, int *rd_fds)
{
	rd_fds[0] = 0;
	rd_fds[1] = 0;
	if (find_token(shell, RD_IN))
		return (redirect_in(shell, rd_fds));
	else if (find_token(shell, RD_HEREDOC))
		redirect_herdoc(shell, rd_fds);
	else if (find_token(shell, RD_OUT))
		return (redirect_out(shell, rd_fds));
	else if (find_token(shell, RD_APPEND))
		return (redirect_app(shell, rd_fds));
	return (1);
}
