/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:15:38 by hkwon             #+#    #+#             */
/*   Updated: 2021/10/18 19:22:28 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** command name이 필요한가?
*/
t_cmd	*make_cmd(char *cmd_list)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->token = parse_token(cmd_list);
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

t_cmd	*make_cmd_list(char **cmd_list)
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	t_token *target;
	int		i;

	i = -1;
	cmd = NULL;
	while (cmd_list[++i])
	{
		tmp = make_cmd(cmd_list[i]);
		//test
		if(cmd_list[i+1] == NULL)
			tmp->pipe_flag = 0;
		else
			tmp->pipe_flag = 1;
		//test end
		//test2
		target = tmp->token;
		while (target)
		{
			if (target->type == RD_OUT)
			{
				tmp->re_flag = 1;
			}
			target = target->next;
		}
		//test2 end
		if (!tmp)
			return (NULL);
		if (cmd == NULL)
			cmd = tmp;
		else
		{
			cmd->next = tmp;
			tmp->prev = cmd;
			cmd = cmd->next;
		}
	}
	ft_free_arr(cmd_list);
	while (cmd->prev)
		cmd = cmd->prev;
	return (cmd);
}

t_cmd	*parse_start(char *line)
{
	char	**cmd_list;
	t_cmd	*tmp;

	if (!line)
		return (NULL);
	cmd_list = parse_line(line);
	//end
	if (!cmd_list)
		return (NULL);
	t_cmd *temp = make_cmd_list(cmd_list);
	return (temp);
}
