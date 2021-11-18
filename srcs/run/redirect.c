/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 07:27:54 by ysong             #+#    #+#             */
/*   Updated: 2021/11/18 18:50:15 by hkwon            ###   ########.fr       */
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
	int		fd;
	int		test_r;
	char	*end;
	char	*buf;
	int		temp_fileno;

	fd = open(".temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (shell->cmd->prev && shell->cmd->prev->pipe_flag && \
		!shell->cmd->next)
		temp_fileno = STDOUT_FILENO;
	else if (shell->cmd->next && !shell->cmd->prev)
		temp_fileno = STDIN_FILENO;
	else if (shell->cmd->next && shell->cmd->prev)
		temp_fileno = shell->cmd->prev->fds[1];
	else
		temp_fileno = STDIN_FILENO;
	end = find_token(shell, RD_HEREDOC);
	write(temp_fileno, "> ", 2);
	while ((test_r = get_next_line(temp_fileno, &buf)) > 0)
	{
		// tcgetattr(STDIN_FILENO, &g_mini.org_term);
		// tcgetattr(STDIN_FILENO, &g_mini.new_term); // STDIN으로부터 터미널 속성을 받아온다
		// g_mini.new_term.c_lflag &= ~(ICANON | ECHO);  // ICANON, ECHO 속성을 off
		// g_mini.new_term.c_cc[VMIN] = 1;               // 1 바이트씩 처리
		// g_mini.new_term.c_cc[VTIME] = 0;              // 시간은 설정하지 않음
		// tcsetattr(STDIN_FILENO, TCSANOW, &g_mini.new_term); // 변경된 속성의 터미널을 STDIN에 바로 적용
		if (!ft_strcmp(buf, end))
			break ;
		write(fd, buf, strlen(buf));
		write(fd, "\n", 1);
		write(temp_fileno, "> ", 2);
		free(buf);
		// tcsetattr(STDIN_FILENO, TCSANOW, &g_mini.org_term);
	}
	if (!(fd <= 2))
		close(fd);
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
