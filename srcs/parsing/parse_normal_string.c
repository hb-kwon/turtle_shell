/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_normal_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:31:57 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/19 21:25:33 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_no_question(char **res, char *args, int *i)
{
	char	*name;
	char	*temp;

	name = NULL;
	temp = NULL;
	while (!ft_strchr(" =$\t\n\"\'\\/", args[++(*i)]))
		name = ft_charjoin(name, args[*i]);
	temp = set_value(find_value(name, g_mini.envp), 0);
	*res = ft_strjoin_free(*res, temp, 3);
	if (name)
		free(name);
}

int	parse_normal_string(char **res, char *args, int i)
{
	if (args[i] == '$')
	{
		if (args[i + 1] == '?')
		{
			*res = ft_strjoin_free(*res, ft_itoa(g_mini.exit_status), 3);
			i += 2;
		}
		else
			get_no_question(res, args, &i);
	}
	else
		*res = ft_charjoin(*res, args[i++]);
	return (i);
}
