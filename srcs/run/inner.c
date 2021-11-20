/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:53:10 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/20 14:38:33 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_path_err(char *arg, char *err, int err_num, char **path)
{
	ft_putstr_fd("minishell :", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err, 2);
	g_mini.exit_status = err_num;
	free(*path);
	return (0);
}

static int	path_error_check(char **path, t_mini *shell)
{
	struct stat	s;
	char		*arg;

	arg = find_token(shell, COMMAND);
	if (!stat(*path, &s) && S_ISDIR(s.st_mode))
		return (print_path_err(arg, "is a directory", 126, path));
	if (!stat(*path, &s) && !(s.st_mode & S_IXUSR))
		return (print_path_err(arg, "Permission denied", 126, path));
	if (!*path || !ft_strchr(*path, '/'))
	{
		if (!stat(find_token(shell, COMMAND), &s))
			*path = find_token(shell, COMMAND);
		else
			return (print_path_err(arg, "command not found", 127, path));
	}
	if (stat(*path, &s))
		return (print_path_err(arg, "No such file or directory", 127, path));
	return (1);
}

static int	run_inner_child(t_mini *shell, int *rd_fds)
{
	char	*path;
	int		i;
	char	**buff;

	buff = make_buff(shell);
	pipe_process(shell);
	path = find_path(shell, find_token(shell, COMMAND));
	if (!path_error_check(&path, shell))
		exit(g_mini.exit_status);
	if (!redirect_process(shell, rd_fds))
		exit (1);
	i = -1;
	while (buff[++i])
	{
		if (execve(path, buff, shell->envp) == -1)
			exit(EXIT_FAILURE);
	}
	free(path);
	free(buff);
	exit(EXIT_SUCCESS);
}

static void	run_inner_parent(t_mini *shell)
{
	int	status;

	wait(&status);
	if (status >> 8 == 255)
		g_mini.exit_status = 255;
	else if (g_mini.sig_on)
		g_mini.exit_status = status + 128;
	else if (status >> 8 != 0)
		g_mini.exit_status = status >> 8;
	else
		g_mini.exit_status = 0;
	(void)shell;
}

int	run_inner(t_mini *shell)
{
	int		old_fds[2];
	int		rd_fds[2];

	save_old_fds(old_fds);
	pipe(shell->cmd->fds);
	g_mini.pid = fork();
	if (g_mini.pid == 0)
		run_inner_child(shell, rd_fds);
	else if (g_mini.pid == -1)
		print_error1("fork error", strerror(errno));
	else
	{
		run_inner_parent(shell);
		redirect_close(rd_fds);
		pipe_restore(shell, old_fds);
	}
	return (1);
}
