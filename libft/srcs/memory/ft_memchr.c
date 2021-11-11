/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 03:54:10 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/11 21:21:55 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t size)
{
	const unsigned char	*s;

	s = (const unsigned char *)ptr;
	while (size--)
	{
		if (*s == (unsigned char)value)
			return ((void*) s);
		s++;
	}
	return (0);
}
