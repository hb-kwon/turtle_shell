/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:22:25 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/11 03:26:57 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isdigit_str(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (!ft_isdigit(str[idx]))
			return (0);
		idx++;
	}
	return (1);
}

int	ft_exit(t_mini *shell)
{
	int		ac;
	int		status;
	char	**buff;

	buff = make_buff(shell);
	ac = 0;
	status = 1;
	while (buff[ac])
		ac++;
	ft_putstr_fd("exit\n", 2);
	if (ac == 1)
		status = 0;
	else if (ac == 2 && ft_isdigit_str(buff[1]))
		status = ft_atoi(buff[1]);
	else if (ac > 2 && ft_isdigit_str(buff[1]))
		print_error1("exit", "too many argments");
	else
	{
		print_error2("exit", buff[1], "numeric argument required");
		exit(255);
	}
	g_mini.exit_status = status;
	exit(status);
}
