/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_normal_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:31:57 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/12 19:59:12 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*get_env_set_envp(char *temp, char *res)
// {
// 	int	j;

// 	j = 0;
// 	while (temp && temp[j])
// 	{
// 		if (!ft_strchr("\t\n ", temp[j]))
// 		{
// 			res = ft_charjoin(res, ' ');
// 			while (!ft_strchr("\t\n ", temp[j]))
// 				j++;
// 		}
// 		else
// 		{
// 			res = ft_charjoin(res, temp[j]);
// 			j++;
// 		}
// 	}
// 	return (res);
// }

static void	get_no_question(char **res, char *args, int *i)
{
	char	*name;
	char	*temp;

	name = NULL;
	temp = NULL;
	while (!ft_strchr(" \t\n\"\'\\/", args[++(*i)]))
		name = ft_charjoin(name, args[*i]);
	temp = set_value(find_value(name, g_mini.envp), 0);
	if (temp == NULL)
		*res = ft_strjoin_free(*res, "$", 1);
	else
		*res = ft_strjoin_free(*res, temp, 1);
	if (name)
		free(name);
	if (temp)
		free(temp);
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
		{
			printf("debug start\n");
			get_no_question(res, args, &i);
		}
	}
	else
		*res = ft_charjoin(*res, args[i++]);
	return (i);
}
