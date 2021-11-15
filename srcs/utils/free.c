/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 18:54:37 by ysong             #+#    #+#             */
/*   Updated: 2021/11/15 19:16:01 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *tkn)
{
	t_token	*temp;
	t_token	*keep;

	temp = tkn;
	keep = NULL;
	while (temp->prev)
		temp = temp->prev;
	while (temp)
	{
		keep = temp;
		temp = temp->next;
		keep->next = NULL;
		keep->prev = NULL;
		free(keep->arg);
		free(keep);
	}
}

void	free_cmd(t_mini *shell)
{
	t_cmd	*temp;
	t_cmd	*keep;

	keep = NULL;
	temp = shell->cmd;
	while (temp->prev)
		temp = temp->prev;
	while (temp)
	{
		keep = temp;
		temp = temp->next;
		free_token(keep->token);
		keep->next = NULL;
		keep->prev = NULL;
		free(keep);
	}
}

void	ft_free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
