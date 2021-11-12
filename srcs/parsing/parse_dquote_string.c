/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dquote_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:30:56 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/13 02:29:05 by hkwon            ###   ########.fr       */
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
		if (name == NULL)
			*res = ft_strjoin_free(*res, "$", 1);
		temp = set_value(find_value(name, g_mini.envp), 0);
		*res = ft_strjoin_free(*res, temp, 3);
	}
	if (name)
		free(name);
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
