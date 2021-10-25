/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_i_to_j.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:14:43 by hkwon             #+#    #+#             */
/*   Updated: 2021/10/25 16:18:36 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strcpy_i_to_j(char *line, int i, int j)
{
	char	*result;
	int		k;

	// printf("line check : %c\n", line[i]);
	// if (line[i] == '\'' || line[i] == '\"')
	// 	i++;
	result = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!result)
		return (NULL);
	k = 0;
	while (i < j)
		result[k++] = line[i++];
	result[k] = '\0';
	return (result);
}
