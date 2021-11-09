/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 16:45:14 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/09 19:36:49 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(char ***en, char *envp[])
{
	int	i;
	int	j;

	i = -1;
	while (envp[++i])
		;
	(*en) = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
	{
		(*en)[i] = (char *)malloc(PATH_MAX + 1);
		j = -1;
		while (envp[i][++j])
			(*en)[i][j] = envp[i][j];
		(*en)[i][j] = 0;
	}
	(*en)[i] = 0;
	// g_mini.envp = *en;
	return ;
}

static void signal_int(int signo)
{
	if (g_mini.pid > 0)
	{
		if (!kill(g_mini.pid, signo))
		{
			printf("\n");
			g_mini.sig_on = 1;
		}
		else
		{
			//mac
			//printf("\033[%luC  \b\b\n", ft_strlen(g_mini.path));
			//window
			printf("\b\b  \b\b\n");
			if (rl_on_new_line() == -1)
				exit(1);
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else
	{
		//mac
		// printf("\033[%luC  \b\b\n", ft_strlen(g_mini.path));
		//window
		printf("\b\b  \b\b\n");
		if (rl_on_new_line() == -1)
			exit(1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	signal_quit(int signo)
{
	if (g_mini.pid > 0)
	{
		if (!kill(g_mini.pid, signo))
		{
			printf("Quit: 3\n");
			g_mini.sig_on = 1;
		}
		else
			//mac
			//printf("\033[%luC  \b\b", ft_strlen(g_mini.path));
			//window
			printf("\b\b  \b\b");
	}
	else
		printf("\b\b  \b\b");
}

void	init_shell(char ***en, char *envp[])
{
	init_env(en, envp);
	signal(SIGINT, signal_int);
	signal(SIGQUIT, signal_quit);
}

/*
** 터미널을 종료시키는 인터럽트를 발생시켰을 때, 터미널이 종료되는게 아니라 우리의 minishell 프로그램만 종료되도록 액션을 변경해줘야 한다.
** 이런 핸들러 역할을 하는게 아래의 signal 함수이다.
*/
