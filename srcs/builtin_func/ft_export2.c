/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 02:17:30 by ysong             #+#    #+#             */
/*   Updated: 2021/11/16 18:54:20 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_print(char **en, char *key, char *value, int i)
{
	write(1, "declare -x ", ft_strlen("declare -x "));
	write(1, key, ft_strlen(key));
	if (ft_strchr(en[i], '='))
	{
		write(1, "=", 1);
		write(1, "\"", 2);
		write(1, value, ft_strlen(value));
		write(1, "\"", 2);
	}
	write(1, "\n", 2);
}

int	is_export_valid(char *str)
{
	int	i;

	i = -1;
	if (ft_isdigit(str[++i]))
		return (0);
	if (str[0] == '$' && str[1])
		return (1);
	if (str[0] == '$' || str[0] == '=')
		return (0);
	return (1);
}

int	export_no_value(char *str, char ***en)
{
	int	i;

	i = -1;
	while ((*en)[++i])
	{
		if (!ft_strncmp((*en)[i], str, ft_strlen(str)))
		{
			return (1);
		}
	}
	add_export(str, en);
	return (1);
}
