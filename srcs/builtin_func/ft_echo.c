/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 14:11:43 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/11/11 22:05:49 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	check_option(t_mini *shell)
// {
// 	t_token	*tmp2;
// 	t_token	*check;
// 	int		j;
// 	int		i;

// 	j = 0;
// 	tmp2 = shell->cmd->token;
// 	check = shell->cmd->token;
// 	while (tmp2)
// 	{
// 		tmp2 = tmp2->next;
// 		j++;
// 	}
// 	i = -1;
// 	while (++i < j)
// 	{
// 		if (!ft_strcmp(check->arg, "-n"))
// 			return (0);
// 		check = check->next;
// 	}
// 	return (1);
// }

static void	print_echo(t_token *token)
{
	while (token)
	{
		if (token->type != ARGUMENT)
			break ;
		else if (token->next && token->next->type == ARGUMENT)
		{
			ft_putstr_fd(token->arg, STDOUT);
			ft_putstr_fd(" ", STDOUT);
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
