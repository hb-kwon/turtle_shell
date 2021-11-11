/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:44:11 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/11 21:08:55 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *res;

	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	ft_memcpy(res, s + start, len);
	res[len] = '\0';
	return (res);
}
