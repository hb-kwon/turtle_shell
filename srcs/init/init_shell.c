/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 16:45:14 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/01 22:08:03 by hkwon            ###   ########.fr       */
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
	// g_mini.envp = *en;
	return ;
}

// final
// terminal setting
// void	init_term(void)
// {
// 	if (tcgetattr(STDIN_FILENO, &g_mini.term_ori) == -1)
// 	{
// 		ft_putstr_fd("error", 2);
// 		exit(1);
// 	}
// 	g_mini.term_sh = g_mini.term_ori;
// 	g_mini.term_sh.c_lflag &= ~(ICANON | ECHO);
// 	g_mini.term_sh.c_lflag |= VEOF;
// 	g_mini.term_sh.c_cc[VMIN] = 1;
// 	g_mini.term_sh.c_cc[VTIME] = 0;
// }
void	init_term()
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &g_mini.term_ori);
	tcgetattr(STDIN_FILENO, &g_mini.term_sh);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_mini.term_sh);
}

void	signal_int(int signum)
{
	if (signum != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

static void int_handler(int status) {
    printf("\n"); // Move to a new line
    rl_on_new_line(); // Regenerate the prompt on a newline
    rl_replace_line("", 0); // Clear the previous text
    rl_redisplay();
}

void	signal_quit(int signum)
{
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	init_shell(char ***en, char *envp[])
{
	init_env(en, envp);
	signal(SIGINT, int_handler);
	signal(SIGQUIT, signal_quit);
	init_term();
}

/*
** 터미널을 종료시키는 인터럽트를 발생시켰을 때, 터미널이 종료되는게 아니라 우리의 minishell 프로그램만 종료되도록 액션을 변경해줘야 한다.
** 이런 핸들러 역할을 하는게 아래의 signal 함수이다.
*/
