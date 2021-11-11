/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:27:46 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/11 18:05:25 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_charjoin(char *str, char c)
{
	int		i;
	int		len;
	char	*res;

	len = ft_strlen(str);
	if (c == '\n')
		return (str);
	else
	{
		res = (char *)malloc(sizeof(char) * (len + 2));
		if (!res)
			return (NULL);
		i = -1;
		if (str == NULL)
			res[0] = c;
		else
		{
			while (str[++i])
				res[i] = str[i];
			res[i] = c;
			free(str);
		}
		res[len + 1] = '\0';
	}
	return (res);
}
