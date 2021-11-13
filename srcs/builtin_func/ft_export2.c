/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 02:17:30 by ysong             #+#    #+#             */
/*   Updated: 2021/11/14 00:41:23 by ysong            ###   ########.fr       */
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

	/*
		키만 들어왔을경우
		기존에 있을 경우 그냥 패스
	*/
	i = -1;
	while ((*en)[++i])
	{
		if(!ft_strncmp((*en)[i], str, ft_strlen(str)))
		{
			return (1);
		}
	}
	add_export(str, en);
	return (1);
}
