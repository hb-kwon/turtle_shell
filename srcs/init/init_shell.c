/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 16:45:14 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/15 17:34:11 by hkwon            ###   ########.fr       */
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
	return ;
}

static void	signal_int(int signo)
{
	// if (g_mini.pid > 0)
	// {
	// 	if (!kill(g_mini.pid, signo))
	// 	{
	// 		printf("\033[%luC  \b\b\n", ft_strlen(g_mini.path));
	// 		g_mini.sig_on = 1;
	// 	}
	// 	else
	// 	{
	// 		printf("\033[%luC  \b\b\n", ft_strlen(g_mini.path));
	// 		if (rl_on_new_line() == -1)
	// 			exit(1);
	// 		rl_replace_line("", 0);
	// 		rl_redisplay();
	// 	}
	// }
	// else
	// {
	// 	printf("\033[%luC  \b\b\n", ft_strlen(g_mini.path));
	// 	if (rl_on_new_line() == -1)
	// 		exit(1);
	// 	rl_replace_line("", 0);
	// 	rl_redisplay();
	// }
	if (g_mini.pid == 0)
	{
			printf("\033[%luC  \b\b\n", ft_strlen(g_mini.path));
			g_mini.sig_on = 1;
	}
	else
	{
		printf("\033[%luC  \b\b\n", ft_strlen(g_mini.path));
		if (rl_on_new_line() == -1)
			exit(1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	signal_quit(int signo)
{
	// if (g_mini.pid > 0)
	// {
	// 	if (!kill(g_mini.pid, signo))
	// 	{
	// 		printf("\033[%luC  \b\bQuit: 3\n", ft_strlen(g_mini.path));
	// 		g_mini.sig_on = 1;
	// 	}
	// 	else
	// 		printf("\033[%luC  \b\b", ft_strlen(g_mini.path));
	// }
	// else
	// 	printf("\033[%luC  \b\b", ft_strlen(g_mini.path));
	if (g_mini.pid == 0)
	{
			printf("\033[%luC  \b\bQuit: 3\n", ft_strlen(g_mini.path));
			g_mini.sig_on = 1;
	}
	else
		printf("\033[%luC  \b\b", ft_strlen(g_mini.path));
}

void	init_shell(char ***en, char *envp[])
{
	init_env(en, envp);
	signal(SIGINT, signal_int);
	signal(SIGQUIT, signal_quit);
}
