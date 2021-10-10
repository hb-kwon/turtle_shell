/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 16:45:14 by hkwon             #+#    #+#             */
/*   Updated: 2021/10/10 18:02:04 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(char ***en, char *envp[])
{
	int	i;
	int	j;

	i = -1;
	while (envp[++i])
		NULL;
	(*en) = (char **)ft_malloc(sizeof(char *) * i);
	i = -1;
	while (envp[++i])
	{
		(*en)[i] = (char *)ft_malloc(PATH_MAX + 1);
		j = -1;
		while (envp[i][++j])
			(*en)[i][j] = envp[i][j];
		(*en)[i][j] = 0;
	}
	(*en)[i] = NULL;
	return ;
}

void	init_term(void)
{
	tcgetattr(STDIN_FILENO, &g_mini.term_sh);
	tcgetattr(STDIN_FILENO, &g_mini.term_ori);
	g_mini.term_sh.c_lflag &= ~(ICANON | ECHO);
	g_mini.term_sh.c_lflag |= VEOF;
	g_mini.term_sh.c_cc[VMIN] = 1;
	g_mini.term_sh.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_mini.term_sh);
}

void	init_termcap(void)
{
	char	*termtype;
	int		success;

	termtype = getenv("TERM");
	if (termtype == 0)
	{
		ft_putstr_fd("minishell: Specify a terminal \
type with `setenv TERM <yourtype>'.", STDERR_FILENO);
		exit(1);
	}
	success = tgetent(NULL, "xterm");
	if (success < 0)
	{
		ft_putstr_fd("minishell: Could not access the \
termcap data base.", STDERR_FILENO);
		exit(1);
	}
	if (success == 0)
	{
		ft_putstr_fd(ft_strjoin_free(ft_strjoin_free("minishell: \
Terminal type `", termtype, 2), "\' is not defined.", 1), STDERR_FILENO);
		exit(1);
	}
}

void	init_shell(char ***en, char *envp[])
{
	init_env(en, envp);
	init_term();
	init_termcap();
}
