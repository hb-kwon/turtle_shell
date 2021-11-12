/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dquote_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:30:56 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/12 19:58:36 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_get_dquote_env(char **res, char *args, int i)
{
	char	*name;
	char	*temp;

	name = NULL;
	temp = NULL;
	if (args[i + 1] == '?')
	{
		*res = ft_strjoin_free(*res, ft_itoa(g_mini.exit_status), 3);
		i += 2;
	}
	else
	{
		while (!ft_strchr(" \t\n\"\'\\/", args[++i]))
			name = ft_charjoin(name, args[i]);
		temp = set_value(find_value(name, g_mini.envp), 0);
		if (temp == NULL)
		*res = ft_strjoin_free(*res, "$", 1);
			else
		*res = ft_strjoin_free(*res, temp, 1);
	}
	if (name)
		free(name);
	if (temp)
		free(temp);
	return (i);
}

int	parse_dquote_string(char **res, char *args, int i)
{
	i++;
	while (args[i] != '\"')
	{
		if (args[i] == '$')
			i = parse_get_dquote_env(res, args, i);
		else
			*res = ft_charjoin(*res, args[i++]);
	}
	i++;
	return (i);
}
