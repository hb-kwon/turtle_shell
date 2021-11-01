/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:30:16 by ysong             #+#    #+#             */
/*   Updated: 2021/11/01 21:44:49 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		turn_on_flag(int *flag, int quote, int idx)
{
	if (*flag & quote)
		*flag ^= quote;
	else
		*flag |= quote;
	idx++;
	return (idx);
}

char	**make_buff(t_mini *shell)
{
	t_token	*temp;
	char	**buff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = shell->cmd->token;
	while (temp)
	{
		temp = temp->next;
		j++;
	}
	buff = (char **)malloc(sizeof(char *) * (j + 1));
	buff[j] = NULL;
	temp = shell->cmd->token;
	while (temp)
	{
		buff[i] = temp->arg;
		temp = temp->next;
		i++;
	}
	return (buff);
}

void free_buff(char **buff)
{
	int i;

	i = -1;
	while (buff[++i])
		free(buff[i]);
	free(buff);
}
