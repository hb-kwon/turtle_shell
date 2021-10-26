/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:02:52 by hkwon             #+#    #+#             */
/*   Updated: 2021/10/26 16:26:47 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	line_input(t_mini *shell)
{
	if (!init_check(g_mini.line))
	{
		add_history(g_mini.line);
		free(g_mini.path);
		free(g_mini.line);
		g_mini.path = NULL;
		g_mini.line = NULL;
		return (0);
	}
	else
		shell->cmd = parse_start(g_mini.line);
	add_history(g_mini.line);
	free(g_mini.path);
	free(g_mini.line);
	g_mini.path = NULL;
	g_mini.line = NULL;
	return (1);
}

static void	line_enter(void)
{
	free(g_mini.path);
	free(g_mini.line);
	g_mini.path = NULL;
	g_mini.line = NULL;
}

static void	line_eof(void)
{
	printf("\x1b[1A\033[%zuCexit\n", ft_strlen(g_mini.path));
	free(g_mini.path);
	free(g_mini.line);
	g_mini.path = NULL;
	g_mini.line = NULL;
	exit(0);
}

int	init_line(t_mini *shell)
{
	char	buf[PATH_MAX];

	g_mini.path = ft_strjoin(getcwd(buf, PATH_MAX), "$ ");
	g_mini.line = readline(g_mini.path);
	if (g_mini.line == NULL)
		line_eof();
	else if (ft_strchr("", *(g_mini.line)))
		line_enter();
	else
		return (line_input(shell));
	return (1);
}
