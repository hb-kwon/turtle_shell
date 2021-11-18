/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 07:27:54 by ysong             #+#    #+#             */
/*   Updated: 2021/11/18 13:34:34 by ysong            ###   ########.fr       */
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

void	redirect_herdoc(t_mini *shell, int *rd_fds)
{
	// char	*r;
	char	*end;
	int		fd;
	char	*buf;
	char	*r;
	int		test_r;
	int		test;


	fd = open(".temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 파이프가 있으면 다르게 작동하도록 하자
	if (shell->cmd->prev && shell->cmd->prev->pipe_flag)
		{test = dup2(fd, shell->cmd->prev->fds[0]);
		test = fd;}
	else
		test = STDIN_FILENO;
	// printf("shell->cmd->pipe_flag = %d\n",shell->cmd->prev->pipe_flag);
	// printf("test = %d\n",test);
	end = find_token(shell, RD_HEREDOC);
	write(STDOUT_FILENO, "> ", 2);
	int line = 1;
	// printf("test%d\n",line++);
	while ((test_r = get_next_line(STDOUT_FILENO, &buf)) > 0)
	{
		// printf("test%d\n",line++);
		// if (!ft_strcmp(buf, end))
		if (end[0] == buf[0])
			break ;
		// printf("test%d\n",line++);
		write(fd, buf, strlen(buf));
		write(fd, "\n", 1);
		write(STDOUT_FILENO, "> ", 2);
		free(buf);
		// printf("test%d\n",line++);
	}
	// if (buf)
	// 	free(buf);
	if (!(fd <= 2))
		close(fd);
	rd_fds[0] = open(".temp.txt", O_RDONLY);
	// printf("test%d\n",line++);
	// dup2(fd, test);
	if (shell->cmd->prev && shell->cmd->prev->pipe_flag)
		dup2(rd_fds[0], STDIN_FILENO);
	else
		dup2(rd_fds[0], STDIN_FILENO);
	// printf("shell->cmd->pipe_flag = %d\n",shell->cmd->prev->pipe_flag);
	// printf("test%d\n",line++);
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
