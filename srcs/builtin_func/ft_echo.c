/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 14:11:43 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/11/07 19:06:20 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_option(t_mini *shell)
{
	t_token	*tmp2;
	t_token	*check;
	int		j;
	int		i;

	j = 0;
	tmp2 = shell->cmd->token;
	check = shell->cmd->token;
	while (tmp2)
	{
		tmp2 = tmp2->next;
		j++;
	}
	i = -1;
	while (++i < j)
	{
		if (!ft_strcmp(check->arg, "-n"))
			return 0;
		check = check->next;
	}
	return (1);
}

void print_exit_status(t_mini *shell)
{
	ft_putstr_fd(ft_itoa(shell->exit_status), STDOUT);
}

static void echo_home(char *arg, t_mini *shell)
{
	char *temp;
	if(arg[1] == '?')
		print_exit_status(shell);
	temp = find_en(&(arg[1]), shell->envp);
	ft_putstr_fd(temp, STDOUT);
}

int	ft_echo(t_mini *shell)
{
	int		n_flag;
	t_token *token;

	token = shell->cmd->token->next;
	n_flag = 0;
	if (!check_option(shell))
	{
		token = token->next;
		n_flag = 1;
	}
	while(token)
	{
		if (token->type != ARGUMENT)
			break ;
		if (token->arg[0] == '$')
		{
			echo_home(token->arg, shell);
			break;
		}
		else
		{
			ft_putstr_fd(token->arg, STDOUT);
			ft_putstr_fd(" ", STDOUT);
		}
		token = token->next;
	}
	if (n_flag)
		return (0);
	write(1, "\n", 1);
	return (0);
}
