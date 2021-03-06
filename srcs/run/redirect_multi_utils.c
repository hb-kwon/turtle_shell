/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_multi_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:27:10 by ysong             #+#    #+#             */
/*   Updated: 2021/11/20 14:48:19 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	multi_redirect_in(char *open_file, int *rd_fds)
{
	if ((access(open_file, R_OK) == -1) && (errno == EACCES))
		return (print_path_err(open_file, \
		"Permission denied", 126, &open_file));
	close(rd_fds[0]);
	rd_fds[0] = open(open_file, O_RDONLY);
	if (rd_fds[0] == -1)
		return (print_path_err(open_file, \
		"No such file or directory", 127, &open_file));
	dup2(rd_fds[0], STDIN_FILENO);
	return (1);
}

void	multi_redirect_herdoc(t_mini *shell, int *rd_fds, char *end)
{
	int		fd;
	int		temp;
	char	*buf;
	int		fileno;

	fd = open(".temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	set_fileno(shell, &fileno);
	write(fileno, "> ", 2);
	temp = get_next_line(fileno, &buf);
	while (temp > 0)
	{
		if (!ft_strcmp(buf, end))
			break ;
		ft_print_heredoc(fd, buf, fileno);
		temp = get_next_line(fileno, &buf);
	}
	if (buf)
		free(buf);
	if (!(fd <= 2))
		close(fd);
	rd_fds[0] = open(".temp.txt", O_RDONLY);
	dup2(rd_fds[0], STDIN_FILENO);
	unlink(".temp.txt");
}

int	multi_redirect_out(char *open_file, int *rd_fds)
{
	if (access(open_file, W_OK) == -1 && errno == EACCES)
		return (print_path_err(open_file, \
		"Permission denied", 126, &open_file));
	if (rd_fds[1] > 0)
		close(rd_fds[1]);
	rd_fds[1] = open(open_file, \
	O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(rd_fds[1], STDOUT_FILENO);
	return (1);
}

int	multi_redirect_app(char *open_file, int *rd_fds)
{
	if (access(open_file, W_OK) == -1 && errno == EACCES)
		return (print_path_err(open_file, \
		"Permission denied", 126, &open_file));
	if (rd_fds[1] > 0)
		close(rd_fds[1]);
	rd_fds[1] = open(open_file, \
	O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(rd_fds[1], STDOUT_FILENO);
	return (1);
}

int	check_multi_rd(t_mini *shell)
{
	int	in_count;
	int	out_count;

	in_count = count_rd_option(shell, 1);
	out_count = count_rd_option(shell, 0);
	if ((in_count == 0 && out_count == 0) || \
		(in_count == 1 && out_count == 0) || \
		(in_count == 0 && out_count == 1))
		return (0);
	return (1);
}
