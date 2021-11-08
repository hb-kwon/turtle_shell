/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 07:27:54 by ysong             #+#    #+#             */
/*   Updated: 2021/11/08 09:33:27 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_in(t_mini *shell, int *rd_fds)
{
	if (rd_fds[0] > 0)
		close(rd_fds[0]);
	rd_fds[0] = open(find_token(shell, ARG), O_RDONLY);
	//todo
	if (rd_fds[0] == -1)
		// return (ft_print_err(find_token(shell, ARG), strerror(errno), NULL, 1));
		return (-1);
	dup2(rd_fds[0], STDIN_FILENO);
	return (1);
}
void	ft_close(int fd)
{
	if (fd <= 2)
		return ;
	close(fd);
}
static int	redirect_herdoc(t_mini *shell, int *rd_fds)
{
	char *r;
	char *end;
	int fd;
	//임의의 파일을 만들어서 그걸 입력으로 넣기?
	if (fd > 0)
		close(fd);
	rd_fds[0] = open(".temp.txt",O_WRONLY | O_CREAT | O_TRUNC, 0644);
	end = find_token(shell, RD_HEREDOC);
	write(1, "> ", 2);
	r = readline(g_mini.path);
	while (r > 0)
	{
		if (ft_strcmp(r, end) == 0)
			break;
		write(1, "> ", 2);
		write(rd_fds[0], r, strlen(r));
		write(rd_fds[0], "\n", 1);
		r = readline(g_mini.path);

	}
	ft_close(fd);
	rd_fds[0] = open(".temp.txt", O_RDONLY);
	dup2(rd_fds[0], STDIN_FILENO);
}
static void	redirect_out(t_mini *shell, int *rd_fds)
{
	if (rd_fds[1] > 0)
		close(rd_fds[1]);
	rd_fds[1] = open(find_token(shell, ARG), O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(rd_fds[1], STDOUT_FILENO);
}

static void	redirect_app(t_mini *shell, int *rd_fds)
{
	if (rd_fds[1] > 0)
		close(rd_fds[1]);
    rd_fds[1] =	open(find_token(shell, ARG), O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(rd_fds[1], STDOUT_FILENO);

}

int	redirect_process(t_mini *shell, int *rd_fds)
{
    t_token *target_token;
    int temp;
    rd_fds[0] = 0;
    rd_fds[1] = 0;

    target_token = shell->cmd->token;
    if (find_token(shell, RD_IN))
	{
		redirect_in(shell, rd_fds);
		return (0);
	}
	else if (find_token(shell, RD_HEREDOC))
			redirect_herdoc(shell, rd_fds);
    else if (find_token(shell, RD_OUT))
        redirect_out(shell, rd_fds);
    else if (find_token(shell, RD_APPEND))
        redirect_app(shell, rd_fds);
    return (1);
}

void		redirect_close(int *rd_fds)
{
	if (rd_fds[0] > 0)
		close(rd_fds[0]);
	if (rd_fds[1] > 0)
		close(rd_fds[1]);
}

void		redirect_restore(int *rd_fds, int *old_fds)
{
	if (rd_fds[0] > 0)
	{
		dup2(old_fds[0], STDIN_FILENO);
		close(rd_fds[0]);
		close(old_fds[0]);
	}
	if (rd_fds[1] > 0)
	{
		dup2(old_fds[1], STDOUT_FILENO);
		close(rd_fds[1]);
		close(old_fds[1]);
	}
}
