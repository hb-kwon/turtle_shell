/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 07:27:54 by ysong             #+#    #+#             */
/*   Updated: 2021/11/17 21:38:59 by ysong            ###   ########.fr       */
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
	// printf("read = %s\n",r);
	// printf("end = %s\n",end);
	while (1)
	{
		if (!ft_strcmp(r, end))
			break ;
		// printf("---\n");
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

	path = find_token(shell, RD_OUT);
	if (access(path, W_OK) == -1 && errno == EACCES)
	{
		print_error1(path, ": Permission denied");
		return (0);
	}
	if (rd_fds[1] > 0)
		close(rd_fds[1]);
	rd_fds[1] = open(find_token(shell, RD_OUT), \
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
	if (check_multi_rd(shell))
		return (multi_rd(shell, rd_fds));
		/*
		멀티 rd_in만 있을경우
		멀티 rd-out만 있을경우
		멀티 두개 다 있을 경우

		*/
	else if (find_token(shell, RD_IN))
		return (redirect_in(shell, rd_fds));
	else if (find_token(shell, RD_HEREDOC))
		redirect_herdoc(shell, rd_fds);
	else if (find_token(shell, RD_OUT))
		return (redirect_out(shell, rd_fds));
	else if (find_token(shell, RD_APPEND))
		return (redirect_app(shell, rd_fds));
	return (1);
}
