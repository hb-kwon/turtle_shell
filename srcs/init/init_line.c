/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:02:52 by hkwon             #+#    #+#             */
/*   Updated: 2021/10/16 18:13:28 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_line(char **line)
{
	char	buf[PATH_MAX];

	g_mini.path = ft_strjoin(getcwd(buf, PATH_MAX), " > ");
	*line = readline(g_mini.path);
	if (*line == NULL)
	{
		//커서를 한 줄 위로, 12칸 뒤로 이동하는 기능
		// ft_putstr_fd("\x1b[1A", STDOUT);
		// ft_putstr_fd("\033[12C", STDOUT);
		printf("\x1b[1A\033[%zuCexit\n", ft_strlen(g_mini.path));
		free(*line);
		free(g_mini.path);
		exit(0);
	}
	else if (ft_strchr("", *(*line)) || !init_check(*line))
	{
		printf("line length : %zu\n", ft_strlen(*line));
		printf("check line space & new line : %s\n", *line);
		*line = NULL;
		free(*line);
	}
	else
	{
		printf("line length : %zu\n", ft_strlen(*line));
		printf("check line correct line : %sEnd\n", *line);
		// g_mini.cmd = parse_start(*line);
		add_history(*line);
		free(*line);
		free(g_mini.path);
		*line = NULL;
	}
}
