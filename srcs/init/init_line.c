/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:02:52 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/05 21:23:37 by ysong            ###   ########.fr       */
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

static int	line_enter(void)
{
	free(g_mini.path);
	free(g_mini.line);
	g_mini.path = NULL;
	g_mini.line = NULL;
	return (0);
}

static void	temp_line_enter(t_mini *shell)
{
	free(g_mini.path);
	free(g_mini.line);
	g_mini.path = NULL;
	g_mini.line = NULL;
	shell->cmd = NULL;
	shell = NULL;
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

	tcsetattr(STDIN_FILENO, TCSANOW, &g_mini.term_ori);
	g_mini.path = ft_strjoin(getcwd(buf, PATH_MAX), "$ ");
	// g_mini.line = (char *)malloc(sizeof(char) * ft_strlen(g_mini.path)+1);
	g_mini.line = readline(g_mini.path);
	if (g_mini.line == NULL)
		line_eof();
	else if (ft_strchr("", *(g_mini.line)))
		temp_line_enter(shell);
	else
		return (line_input(shell));
	return (1);
}
