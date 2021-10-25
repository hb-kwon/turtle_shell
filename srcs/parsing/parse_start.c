/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:15:38 by hkwon             #+#    #+#             */
/*   Updated: 2021/10/25 13:59:20 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** command name이 필요한가?
** command name이 필요한 이유 : blt_func을 실행할 때 문자열을 비교하여 실행하기 위해
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
	t_token	*target;
	int		i;

	i = -1;
	cmd = NULL;
	while (cmd_list[++i])
	{
		tmp = make_cmd(cmd_list[i]);
		//test
		if(cmd_list[i + 1] == NULL)
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

	if (!line)
		return (NULL);
	cmd_list = parse_line(line);
	if (!cmd_list)
		return (NULL);
	return (make_cmd_list(cmd_list));
}
