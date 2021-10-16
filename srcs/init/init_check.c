/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:03:49 by hkwon             #+#    #+#             */
/*   Updated: 2021/10/16 18:14:11 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_check(char *line)
{
	int	i;
	int	f;
	int	rd;

	i = 0;
	if (line == NULL)
		return (0);
	while (line[i])
	{
		printf("line check space before skip : %cEnd\n", line[i]);
		if (ft_strchr("\t\n ", line[i]))
		{
			if (!line[i])
				return (0);
			i++;
		}
		else
			i++;
		printf("line check space after skip : %cEnd\n", line[i]);
	}
	return (1);
}
