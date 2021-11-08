/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:21:40 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/08 17:32:20 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_mini *shell)
{
	int i;

	i = 0;
	while(shell->envp[i])
	{
		write(1, shell->envp[i], ft_strlen(shell->envp[i]));
		write(1,"\n",1);
		i++;
	}
	g_mini.exit_status = 0;
	return (0);
}
