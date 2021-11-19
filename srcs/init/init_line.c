/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:02:52 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/19 15:08:50 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	line_free(void)
{
	free(g_mini.path);
	free(g_mini.line);
	g_mini.path = NULL;
	g_mini.line = NULL;
}

static int	line_input(t_mini *shell)
{
	add_history(g_mini.line);
	if (!init_check(g_mini.line))
	{
		line_free();
		return (0);
	}
	else
		shell->cmd = parse_start(g_mini.line);
	line_free();
	return (1);
}

static int	line_enter(t_mini *shell)
{
	line_free();
	(void)shell;
	return (0);
}

static void	line_eof(t_mini *shell)
{
	printf("\x1b[1A\033[%luCexit\n", ft_strlen(g_mini.path));
	line_free();
	free(shell);
	exit(0);
}

int	init_line(t_mini *shell)
{
	char	buf[PATH_MAX];

	g_mini.path = ft_strjoin(getcwd(buf, PATH_MAX), "$ ");
	g_mini.line = readline(g_mini.path);
	if (!g_mini.line)
		line_eof(shell);
	else if (!line_empty_space(g_mini.line) || ft_strchr("", *(g_mini.line)))
		return (line_enter(shell));
	else
		return (line_input(shell));
	return (0);
}
