/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 02:17:30 by ysong             #+#    #+#             */
/*   Updated: 2021/11/12 00:31:09 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_export_valid(char *str)
{
	int	i;

	i = -1;
	if (ft_isdigit(str[++i]))
		return (0);
	if (str[0] == '$' && str[1])
		return (1);
	if (str[0] == '$')
		return (0);
	return (1);
}

int export_no_value(char *str, char ***en)
{
	int		i;
	char	**new;

	i = -1;
	while ((*en)[++i])
	{
		if(!ft_strncmp((*en)[i], str, ft_strlen(str)))
		{
			(*en)[i] = ft_strdup(str);
			return (1);
		}
	}
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (0);
	i = -1;
	while ((*en)[++i])
		new[i] = ft_strdup((*en)[i]);
	add_export(str, new, i);
	*en = new;
	return (1);
}
