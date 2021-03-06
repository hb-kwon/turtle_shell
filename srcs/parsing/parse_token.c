/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 11:04:30 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/19 16:06:32 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	args_quote(char *cmd_list, int *i, char *flag)
{
	if (cmd_list[*i] == '\"' && !(*flag & D_QUOTE))
	{
		*flag |= D_QUOTE;
		while (*flag & D_QUOTE)
		{
			(*i)++;
			if (cmd_list[*i] == '\"')
				*flag ^= D_QUOTE;
		}
	}
	else if (cmd_list[*i] == '\'')
	{
		while (cmd_list[++(*i)] != '\'')
			;
	}
}

static int	args_count(char *cmd_list)
{
	int		i;
	int		cnt;
	char	flag;

	i = 0;
	cnt = 0;
	flag = 0;
	while (cmd_list[i])
	{
		if (!ft_strchr("<>\t\n ", cmd_list[i]))
		{
			cnt++;
			while (!ft_strchr("<>\t\n ", cmd_list[i]))
			{
				args_quote(cmd_list, &i, &flag);
				i++;
			}
		}
		else
			i++;
	}
	return (cnt);
}

t_token	*parse_token(char *cmd_list)
{
	char	**args;
	int		i;

	if (!cmd_list)
		return (NULL);
	args = (char **)malloc(sizeof(char *) * (args_count(cmd_list) + 1));
	if (!args)
		return (NULL);
	args = parse_token_arr(args, cmd_list);
	i = -1;
	while (args[++i])
	{
		args[i] = parse_token_quote(args[i]);
		if (!args[i])
			break ;
	}
	return (make_token_list(args));
}
