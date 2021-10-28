/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:30:16 by ysong             #+#    #+#             */
/*   Updated: 2021/10/27 22:40:19 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		//debug
		printf("=========DEBUG=========\n");
		printf("buff check : %s\n", buff[i]);
		//end
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

