/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:02:52 by hkwon             #+#    #+#             */
/*   Updated: 2021/10/18 19:44:55 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_line(t_mini *shell)
{
	char	buf[PATH_MAX];

	//전역변수
	g_mini.path = ft_strjoin(getcwd(buf, PATH_MAX), "$ ");
	g_mini.line = readline(g_mini.path);
	if (g_mini.line == NULL)
	{
		//커서를 한 줄 위로, len만큼 뒤로 이동하는 기능
		printf("\x1b[1A\033[%zuCexit\n", ft_strlen(g_mini.path));
		free(g_mini.path);
		free(g_mini.line);
		g_mini.path = NULL;
		g_mini.line = NULL;
		exit(0);
	}
	else if (ft_strchr("", *(g_mini.line)))
	{
		free(g_mini.path);
		free(g_mini.line);
		g_mini.path = NULL;
		g_mini.line = NULL;
	}
	else
	{
		shell->cmd = parse_start(g_mini.line);
		add_history(g_mini.line);
		free(g_mini.path);
		free(g_mini.line);
		g_mini.path = NULL;
		g_mini.line = NULL;
	}
}
