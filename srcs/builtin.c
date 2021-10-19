/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 13:26:18 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/10/19 16:44:58 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_error_blt(char *str)
{
	write(1, str, strlen(str));
	write(1, " ", 1);
	ft_putstr("commend not found\n");
}

char	*blt_str(int i)
{
	char	*blt_str[BLTIN_NUM + 1];

	blt_str[0] = "echo";
	blt_str[1] = "cd";
	blt_str[2] = "pwd";
	blt_str[3] = "export";
	blt_str[4] = "unset";
	blt_str[5] = "env";
	blt_str[6] = "exit";
	blt_str[7] = NULL;
	return (blt_str[i]);
}

int	(*blt_func(int i))(t_mini *shell)
{
	int	(*blt_func[BLTIN_NUM])(t_mini *shell);

	blt_func[0] = &ft_echo;
	blt_func[1] = &ft_cd;
	blt_func[2] = &ft_pwd;
	blt_func[3] = &ft_export;
	blt_func[4] = &ft_unset;
	blt_func[5] = &ft_env;
	blt_func[6] = &ft_exit;
	return (blt_func[i]);
}

int check_cmd(char *cmd)
{
	char	*builtin;

	builtin = cmd;
	if (!ft_strcmp(builtin, "cd") || !ft_strcmp(builtin, "echo")
	|| !ft_strcmp(builtin, "pwd") || !ft_strcmp(builtin, "env")
	|| !ft_strcmp(builtin, "export") || !ft_strcmp(builtin, "export")
	|| !ft_strcmp(builtin, "unset") || !ft_strcmp(builtin, "exit"))
		return (1);
	return (0);
}
int run_blt(t_mini *shell, int i)
{
	char *cmd;
	
	cmd = shell->cmd->token->arg;
	if(!ft_strcmp(cmd, blt_str(i)))
		(*blt_func(i))(shell);
	else if(i == 6 && !check_cmd(cmd))
		print_error_blt(cmd);
	return 0;
}
