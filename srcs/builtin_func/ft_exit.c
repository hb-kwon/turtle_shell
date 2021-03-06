/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:22:25 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/19 15:08:58 by hkwon            ###   ########.fr       */
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

static void	ft_exit_process(int ac, int *status, char **buff)
{
	if (ac == 1)
		*status = 0;
	else if (ac == 2 && ft_isdigit_str(buff[1]))
		*status = ft_atoi(buff[1]);
	else if (ac > 2 && ft_isdigit_str(buff[1]))
		print_error1("exit", "too many argments");
	else
	{
		print_error2("exit", buff[1], "numeric argument required");
		*status = 255;
	}
}

int	ft_exit(t_mini *shell)
{
	int		ac;
	int		status;
	char	**buff;

	buff = make_buff(shell);
	ac = 0;
	status = 1;
	if (shell->cmd->pre_flag == 1)
		return (0);
	while (buff[ac])
		ac++;
	ft_putstr_fd("exit\n", 2);
	ft_exit_process(ac, &status, buff);
	free(buff);
	g_mini.exit_status = status;
	exit(status);
}
