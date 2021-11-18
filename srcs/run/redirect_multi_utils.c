/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_multi_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:27:10 by ysong             #+#    #+#             */
/*   Updated: 2021/11/18 20:54:12 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	multi_redirect_in(char *open_file, int *rd_fds)
{

	if (access(open_file, R_OK) == -1 && errno == EACCES)
	{
		print_error1(open_file, "Permission denied");
		return (0);
	}
	if (rd_fds[0] > 0)
		close(rd_fds[0]);
	rd_fds[0] = open(open_file, O_RDONLY);
	if (rd_fds[0] == -1)
	{
		print_error1(open_file, \
		"No such file or directory");
		return (0);
	}
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
	while ((temp = get_next_line(fileno, &buf)) > 0)
	{
		if (!ft_strcmp(buf, end))
		{
			free(buf);
			break ;
		}
		write(fd, buf, strlen(buf));
		write(fd, "\n", 1);
		write(fileno, "> ", 2);
		free(buf);
	}
	if (!(fd <= 2))
		close(fd);
	rd_fds[0] = open(".temp.txt", O_RDONLY);
	dup2(rd_fds[0], STDIN_FILENO);
	unlink(".temp.txt");
}

int	multi_redirect_out(char *open_file, int *rd_fds)
{
	if (access(open_file, W_OK) == -1 && errno == EACCES)
	{
		print_error1(open_file, ": Permission denied");
		return (0);
	}
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
	{
		print_error1(open_file, ": Permission denied");
		return (0);
	}
	if (rd_fds[1] > 0)
		close(rd_fds[1]);
	rd_fds[1] = open(open_file, \
	O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(rd_fds[1], STDOUT_FILENO);
	return (1);
}

int check_multi_rd(t_mini *shell)
{
    int in_count;
    int out_count;

	in_count = count_rd_option(shell, 1);
	out_count = count_rd_option(shell, 0);
    if ((in_count == 0 && out_count == 0) || \
        (in_count == 1 && out_count == 0) || \
        (in_count == 0 && out_count == 1))
			return (0);
    return (1);
}
