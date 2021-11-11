/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 02:17:30 by ysong             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/11/11 22:16:09 by hkwon            ###   ########.fr       */
=======
/*   Updated: 2021/11/11 22:06:20 by ysong            ###   ########.fr       */
>>>>>>> 63af60abffcf96ccc9c912e7d4299fde4bbf9fff
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
