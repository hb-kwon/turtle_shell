/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:23:36 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/19 15:01:11 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_heredoc(int fd, char *buf, int fileno)
{
	write(fd, buf, strlen(buf));
	write(fd, "\n", 1);
	write(fileno, "> ", 2);
}

int	ft_print_synerr(char c)
{
	ft_putstr_fd("minishell: syntax error\'", STDERR_FILENO);
	write(STDERR_FILENO, &c, 1);
	ft_putstr_fd("\'\n", STDERR_FILENO);
	g_mini.exit_status = 258;
	return (0);
}

int	print_error1(char *msg, char *err_num)
{
	ft_putstr_fd("minishell :", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err_num, 2);
	return (-1);
}

int	print_error2(char *msg1, char *msg2, char *err_num)
{
	ft_putstr_fd("minishell :", 2);
	ft_putstr_fd(msg1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg2, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err_num, 2);
	return (-1);
}

void	print_error_blt(char *str)
{
	write(1, str, strlen(str));
	write(1, " ", 1);
	ft_putstr("commend not found\n");
}
