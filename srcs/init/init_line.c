/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:02:52 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/09 22:07:03 by hkwon            ###   ########.fr       */
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
	{
		shell->cmd = parse_start(g_mini.line);
		if (!shell->cmd)
			return (0);
	}
	add_history(g_mini.line);
	free(g_mini.path);
	free(g_mini.line);
	g_mini.path = NULL;
	g_mini.line = NULL;
	return (1);
}

static int	line_enter(t_mini *shell)
{
	free(g_mini.path);
	free(g_mini.line);
	g_mini.path = NULL;
	g_mini.line = NULL;

	return (0);
}

static void	line_eof(t_mini *shell)
{
	free_cmd(shell);
	free(shell);
	printf("\x1b[1A\033[%luCexit\n", ft_strlen(g_mini.path));
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
	if (!g_mini.line)
		line_eof(shell);
	else if (ft_strchr("", *(g_mini.line)))
		return (line_enter(shell));
	else
		return (line_input(shell));

	// int	i;

	// if (!g_mini.line)
	// 	line_eof(shell);
	// i = 0;
	// while (g_mini.line[i] == ' ')
	// 	i++;
	// if (!g_mini.line[i])
	// {
	// 	free(g_mini.path);
	// 	free(g_mini.line);
	// 	shell->cmd = NULL;
	// 	shell = NULL;
	// 	return (0);
	// }
	// else
	// 	return (line_input(shell));
	// return (1);
}
