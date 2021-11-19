/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 14:11:43 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/11/19 15:40:39 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo(t_token *token)
{
	while (token)
	{
		if (token->type != ARGUMENT)
			break ;
		else if (token->next && token->next->type == ARGUMENT)
		{
			if (token->arg[0] != '\0')
			{
				ft_putstr_fd(token->arg, STDOUT);
				ft_putstr_fd(" ", STDOUT);
			}
		}
		else
			ft_putstr_fd(token->arg, STDOUT);
		token = token->next;
	}
}

int	ft_echo(t_mini *shell)
{
	int		n_flag;
	t_token	*token;

	token = shell->cmd->token->next;
	n_flag = 0;
	if (token && !ft_strcmp(token->arg, "-n"))
	{
		n_flag = 1;
		token = token->next;
	}
	print_echo(token);
	if (!n_flag)
		write(1, "\n", 1);
	g_mini.exit_status = 0;
	return (0);
}
