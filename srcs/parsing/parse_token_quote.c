/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:27:50 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/19 15:57:51 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_value(char *arg, int idx)
{
	int		flag;
	char	*res;

	if (!arg)
		return (NULL);
	flag = 0;
	res = NULL;
	while (arg[idx])
	{
		if (arg[idx] == '\"' && !(flag & S_QUOTE))
			idx = turn_on_flag(&flag, D_QUOTE, idx);
		else if (arg[idx] == '\'' && !(flag & D_QUOTE))
			idx = turn_on_flag(&flag, S_QUOTE, idx);
		else
			res = ft_charjoin(res, arg[idx++]);
	}
	return (res);
}

char	*parse_token_quote(char *args)
{
	char	*res;
	int		i;

	res = NULL;
	i = 0;
	while (args[i])
	{
		if (args[i] == '\'')
		{
			i++;
			while (args[i] != '\'')
				res = ft_charjoin(res, args[i++]);
			i++;
		}
		else if (args[i] == '\"')
			i = parse_dquote_string(&res, args, i);
		else
			i = parse_normal_string(&res, args, i);
	}
	free(args);
	return (res);
}
